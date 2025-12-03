#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <random>
#include <chrono>
#include <limits>
#include <algorithm>
const int MAX_FIELD_LEN = 64; 
const std::string FNAME = "passwords.bin"; 

static std::default_random_engine engine(
    std::chrono::system_clock::now().time_since_epoch().count()
);

struct PasswordEntry{
	char host[MAX_FIELD_LEN];
	char url[MAX_FIELD_LEN];
	char username[MAX_FIELD_LEN];
	char password[MAX_FIELD_LEN];
};

void display_banner();

std::string generate(int len){
	const char char_set[] = 
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()_+-=[]{};:,.<>/?";
        
    size_t char_set_len = std::strlen(char_set);
    std::string pass;
    pass.reserve(len);
	
	std::uniform_int_distribution<size_t> distribution(0, char_set_len - 1);
	
	for (int i=0; i<len; i++){
		size_t random_index = distribution(engine);
		pass += char_set[random_index];
	}
	
	return pass;
}

void set_field(char target[], const std::string& source) {
    std::strncpy(target, source.c_str(), MAX_FIELD_LEN - 1);
    target[MAX_FIELD_LEN - 1] = '\0'; 
}

PasswordEntry get_user_input(){
	PasswordEntry new_entry;
	std::string tmp_input;
	
	std::cout << "\n--- Enter New Password Entry ---" << std::endl;
	
	std::cout << "Enter Host/Site Name: ";
	std::getline(std::cin, tmp_input);
	set_field(new_entry.host, tmp_input);
	
	std::cout << "Enter URL: ";
	std::getline(std::cin, tmp_input);
	set_field(new_entry.url, tmp_input);
	
	std::cout << "Enter Username/Email: ";
	std::getline(std::cin, tmp_input);
	set_field(new_entry.username, tmp_input);
	
	tmp_input = generate(16);
	std::cout<<"Your generated Password is: " << tmp_input<<std::endl;
	set_field(new_entry.password, tmp_input);
	
	return new_entry;
}

void save_entries(const std::vector<PasswordEntry>& entries){
	std::fstream file(FNAME, std::ios::binary | std::ios::out);
	
	if (!file.is_open()){
		std::cerr << "ERROR: Could not open file for writing: " << FNAME << std::endl;
		return;
	}
	
	file.write(reinterpret_cast<const char*>(entries.data()), entries.size() * sizeof(PasswordEntry));
	
	file.close();
	std::cout << "\nSuccessfully saved " << entries.size()<< " entries to " << FNAME << std::endl;
}

std::vector<PasswordEntry> load_entries(){
	std::vector<PasswordEntry> entries;
	std::fstream file(FNAME, std::ios::binary | std::ios::in);
	
	if(!file.is_open()){
		std::cout << "\nFile not found. Returning empty list." << std::endl;
		return entries;
	}
	
	file.seekg(0, std::ios::end);
	long file_size = file.tellg();
	file.seekg(0, std::ios::beg);
	
	if (file_size == 0 || file_size % sizeof(PasswordEntry) != 0){
		std::cerr << "ERROR: File size is corrupted or empty." << std::endl;
		file.close();
		return entries;
	}
	
	size_t num_entries = file_size / sizeof(PasswordEntry);
	
	entries.resize(num_entries);
	
	file.read(reinterpret_cast<char*>(entries.data()), file_size);
	
	file.close();
	std::cout << "\nSuccessfully loaded " << entries.size()<< " entries from " << FNAME << std::endl;
	
	return entries;
}



void update_entry(std::vector<PasswordEntry>& entries){
	std::string target_host;
	std::string new_value;
	int choice;
	
	std::cout << "\n--- Update Password Entry ---" << std::endl;
	std::cout << "Enter the Host/Site Name to update: ";
	std::getline(std::cin, target_host);
	
	auto it = std::find_if(entries.begin(), entries.end(), [&](const PasswordEntry& entry){
		return std::string(entry.host) == target_host;
	});
	
	if (it == entries.end()){
		std::cout << "\nError: Host '" << target_host << "' not found." << std::endl;
		return;
	}
	std::cout << "\nFound entry for: " << it->host << std::endl;
	std::cout << "Which detail do you want to update?" << std::endl;
	std::cout << "1. URL\n2. Username\n3. Password (Generate New)\n> Choice: ";
	
	if(!(std::cin >> choice)){
		std::cout << "Invalid input. Update cancelled." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch(choice){
		case 1:
			std::cout << "Enter new URL: ";
			std::getline(std::cin, new_value);
			set_field(it->url, new_value);
			std::cout << "URL updated successfully." << std::endl;
			break;
		case 2:
			std::cout << "Enter new Username: ";
			std::getline(std::cin, new_value);
			set_field(it->username, new_value);
			std::cout << "Username updated successfully." << std::endl;
			break;
		case 3:
			new_value = generate(16);
			std::cout << "New Password generated: " << new_value << std::endl;
			set_field(it->password, new_value);
			std::cout << "Password updated successfully." << std::endl;
			break;
		default:
			std::cout << "Invalid choice. Update cancelled." << std::endl;
			break;
	}
}

void delete_entry(std::vector<PasswordEntry>& entries){
	std::string target_host;
	
	std::cout << "\n--- Delete Password Entry ---" << std::endl;
	std::cout << "Enter the Host/Site Name to delete: ";
	std::getline(std::cin, target_host);
	
	auto it = std::remove_if(entries.begin(), entries.end(), [&](const PasswordEntry& entry){
		return std::string(entry.host) == target_host;
	});
	
	if(it == entries.end()){
		std::cout << "\nError: Host '" << target_host << "' not found. No entry deleted." << std::endl;
		return;
	}
	
	size_t deleted_count = std::distance(it, entries.end());
	
	entries.erase(it, entries.end());
	
	std::cout << "\nSuccessfully deleted " << deleted_count << " entry(s) for Host '" << target_host << "'." << std::endl;
}

int main() {
	display_banner();
	std::vector<PasswordEntry> all_entries = load_entries();
	int menu_choice;
	
	do{
		std::cout << "\n\n--- Password Manager Menu ---" << std::endl;
		std::cout << "1. Add New Entry" << std::endl;
		std::cout << "2. Update Detail" << std::endl;
		std::cout << "3. Show All Entries" << std::endl;
		std::cout << "4. Delete Entry" << std::endl;
		std::cout << "5. Exit and Save" << std::endl;
		std::cout << "Enter choice (1-5): ";
		
		if(!(std::cin >> menu_choice)){
			std::cout << "Invalid input. Please enter a number." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		switch(menu_choice){
			case 1:
				all_entries.push_back(get_user_input());
				break;
			case 2:
				update_entry(all_entries);
				break;
			case 3:
				std::cout << "\n--- Current Entries ---" << std::endl;
				if (all_entries.empty()){
					std::cout << "No entries saved yet." << std::endl;
				}
				else{
					for (const auto& entry : all_entries){
						std::cout << "Host: " << entry.host << std::endl << "User: " << entry.username << std::endl << "Password: " << entry.password << std::endl << std::endl;
					}
				}
				break;
			case 4:
				delete_entry(all_entries);
				break;
			case 5:
				std::cout << "\nExiting and saving data..." << std::endl;
				break;
			default:
				std::cout << "Invalid menu choice. Try again." << std::endl;
				break;
		}
		
	}while (menu_choice != 5);
	
	save_entries(all_entries);

	return 0;
}
