#include <iostream>
#include <string>

void display_banner() {
	
    const char* logo[] = {
        "         met$$$ggg.",
        "                 %$R.",
        "          	   &%^^",
        "'$P'%$$PGGG%&#     '$$$.",
        "$$           &*%    '$$b:",
        "dP'           $#%^   ,d$$:",
        "d$'            TR$    $$$",
        "$$:            %$#    $#F%", 
        "$$:                  ,d$$:",
        "$$P                  ,d$$P'",
        "$$   '$P.           '$$b:",
        "$%   '$$.          ,d$$P'",
        "     'Y$.         ,d$$P'",
        "     'Y$.        ,d$P'",
        "     '$Y,%$#J&&F&GH"
        "      "
    };

    std::cout << "\n\n";
    std::cout << "========================================================================\n";
    std::cout << "            				PASSWORD MANAGER PRO   					" << "\n";
    std::cout << "========================================================================\n";
    std::cout << "\n";

    // Print Logo and Project Info Side-by-Side
    int logo_height = sizeof(logo) / sizeof(logo[0]);
    
    // Project Info Lines
    std::string info_lines[] = {
        "->Project: OpenSafe++",
        "->Version: 1.0",
        "->Language: C++11",
        "->Dependencies:",
        "  iostream, fstream, vector, cstring, string,",
        "  random, chrono, limits, algorithm",
        "->Main File: main.cpp",
        "->Banner File: banner.cpp"
    };
    
    int info_index = 0;
    
    for (int i = 0; i < logo_height; ++i) {
        std::cout << logo[i];
        
        // Print corresponding project info line
        if (info_index < sizeof(info_lines) / sizeof(info_lines[0])) {
            std::cout << "  " << info_lines[info_index++];
        }
        std::cout << "\n";
    }

    std::cout << "\n" << std::endl;
    
    std::cout << "*======================================================================*\n";
    std::cout << "| 	?? Secure Your Day with DR_PM ??      			\n";
    std::cout << "|----------------------------------------------------------------------\n";
    std::cout << "|                  Authored by: [DR AMV]                            \n";
    std::cout << "|                  Build Date: " << __DATE__ << "                   \n";
    std::cout << "*======================================================================*\n";
    std::cout <<"\n";

}
