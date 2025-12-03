**OpenSafe++ Password Manager**

**🛡️** **Project Overview**

**OpenSafe++** is a simple, robust, command-line utility designed to securely manage your passwords locally. It stores sensitive data in a compact, persistent binary file (\`passwords.bin\`) and features a strong password generator, creation of new entries, and on-the-fly updating of existing details.

✨ Features

\-\>**Binary Persistence**: All entries are saved efficiently to a binary file (\`passwords.bin\`).

\-\>**Strong Generation**: Generates secure, 16-character alphanumeric passwords with special characters.

\-\>**Interactive Menu**: Easy-to-use command-line menu for CRUD operations (Create, Read, Update, Delete planned).

\-\>**Cross-Platform Ready**: Distributed for both Windows (as a pre-compiled executable) and Linux (as source code).

⚙️ Source Code Dependencies

This project is built using standard \*\*C++11\*\* and requires no external libraries beyond the standard library:

\* \`**iostream**\`

\* \`**fstream**\`

\* \`**vector**\`

\* \`**cstring**\`

\* \`**string**\`

\* \`**random**\`

\* \`**chrono**\`

\* \`**limits**\`

\* \`**algorithm**\`

**🚀** **Installation & Setup Guide**

💻 1. **Windows Users** (Recommended: Use Pre-compiled Executable)

If you download the release package containing the pre-compiled executable, no installation or compilation is necessary.

A. Download and Extract

1\. Download the latest Windows ZIP release from the GitHub \*\*Releases\*\* page.

2\. Extract the contents of the ZIP file to a folder of your choice (e.g., \`C:\\OpenSafePM\`).

3\. The extracted folder should contain the following files:

\* \`Password_Manager.exe\` (The application)

\* \`main.cpp\`, \`banner.cpp\`, \`Makefile.win\` (Source/Build files)

\* \`passwords.bin\` (The data file, created after first save)

B. Running the Application

1\. Double-click \*\*\`Password_Manager.exe\`\*\* to start the application.

2\. A command prompt window will open displaying the banner and the main menu.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

🐧 2. **Linux Users** (Requires Compilation via g++)

Linux users must compile the source code using the \*\*g++ compiler\*\*.

A. File Setup

1\. Clone or download the source code repository.

2\. Open your terminal and navigate to the project directory containing \`main.cpp\` and \`banner.cpp\`.

B. Build Instructions

Execute the following commands to compile both source files and link them into a single executable named \` Password_Manager_Linux \`:

\`\`\`bash

g++ main.cpp banner.cpp -o Password_Manager_Linux

chmod +x Password_Manager_Linux

./Password_Manager_Linux

**Password Manager Menu (Options 1-5)**

1.  Add New Entry: Prompts for Host/Site, URL, and Username. A strong, 16-character password is automatically generated.
2.  Update Detail: Finds a record by **Host/Site Name** and allows specific modification of the URL, Username, or Password.
3.  Show All Entries: Displays all records currently loaded into memory for review.
4.  Delete Entry: **NEW FEATURE.** Prompts for a **Host/Site Name** and removes the matching record(s) from the active list.
5.  Exit and Save: **CRUCIAL STEP.** Saves all changes (Additions, Updates, Deletions) to the **passwords.bin** file and exits the application safely.
