# Olympics Medal Tracking System

This project implements a system that tracks the Olympic medals won by different nations. The system allows users to manage and display medal counts for each nation, supporting multiple operations such as adding nations, updating medal counts, saving to a file, loading from a file, and displaying the database contents.

## How to run this project

- Go to file project.code - workspace then Open Workspace

- Then run this command in root directory: cd "${positionOfYourFolder}/src/" && gcc project.c -o project && "${positionOfYourFolder}/src
/"project

## Nation Representation

Each nation is represented with the following data:
- **name**: The name of the nation (a string of arbitrary length).
- **gold**: The number of gold medals (a non-negative integer).
- **silver**: The number of silver medals (a non-negative integer).
- **bronze**: The number of bronze medals (a non-negative integer).

The system can support an arbitrary number of nations.

## Supported Commands

### 1. Add Nation
Adds a nation to the database with an initial count of 0 medals.
- **Command Format**: `A <name>`
- **Example**: `A Finland`

If a nation with the specified name already exists in the database, an error message is displayed.

### 2. Add Medals
Adds the specified number of medals to a nation.
- **Command Format**: `M <name> <gold> <silver> <bronze>`
- **Example**: `M Finland 0 1 1`

This command allows negative values for medals to account for adjustments (e.g., due to doping cases). Medal counts cannot be negative overall; if a reduction causes the total to drop below zero, it is adjusted to zero. If the specified nation does not exist, an error message is displayed.

### 3. Print Database
Displays the contents of the database, showing each nation with its corresponding medal counts.
- **Command Format**: `L`
- **Output Format**: `<name> <gold> <silver> <bronze>`
- **Example Output**:

China 2 2 0

Finland 0 2 3

SUCCESS

Nations are listed in the following order:
1. Nations with more gold medals appear first.
2. If gold medals are equal, nations with more silver medals are listed higher.
3. If both gold and silver medals are equal, nations with more bronze medals are prioritized.
4. If all medals are equal, nations can appear in any order.

### 4. Save to File
Saves the current database to a specified text file.
- **Command Format**: `W <filename>`
- **Example**: `W medals.txt`

If an error occurs during saving, an error message is displayed.

### 5. Load from File
Loads nations and their medal counts from a specified text file, replacing the current database.
- **Command Format**: `O <filename>`
- **Example**: `O medals.txt`

The file should contain nations in the format specified above. If an error occurs (e.g., file not found or invalid format), an error message is displayed.

### 6. Quit Program
Releases all allocated memory and exits the program.
- **Command Format**: `Q`

## Example Command Sequence

A China

A Finland

M China 2 1 1 

M Finland 0 0 1

M China 1 3 1 

M China -1 0 0 

L 

W medals

Q


**Explanation**:
- After the above commands, China has 2 gold, 4 silver, and 2 bronze medals, while Finland has 1 bronze medal.
- When listing the database (`L`), China will appear before Finland due to having more medals.
- The database will be saved to the file `medals.txt`.

## Notes
- Ensure the correct format is followed for each command to avoid errors.
- Negative adjustments for medals should not result in negative totals.
