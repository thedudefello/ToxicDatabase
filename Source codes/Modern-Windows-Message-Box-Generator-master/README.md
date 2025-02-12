# Modern Windows Message Box Generator

**Purpose:**  Generates a customizable "Task Dialog" box - a more modern version of the old Windows message box.'

↘️ **How to Download:** Visit the [Releases](https://github.com/ThioJoe/Modern-Windows-Message-Box-Generator/releases) page, and look under "Assets" for the latest release.

## Key Features

- **Set Any Text**: Choose the text to display for each element, or leave it blank to not show that part.
- **Choose Icons:**
    - Select from a range of default icons for both the main icon and title bar icon.
    - Use custom icons from image files. Including image files, icon files, or the icon associated with any Exe file.
    - Choose icons directly from the `imageres.dll` file using their ID.
- **Icon Selection Helper:** Click the "View Icon IDs" button to see icons from `imageres.dll`. Click any of them to automatically set it as the selected icon.
- **Icon Background Colored Bars:** Choose from various colors for the icon background bar, including green, blue, gray, red, yellow, or none.

## More Features:
- **No Installation Required:** The program is a single file and doesn't need to be installed
- **Signed:** The exe is signed with a trusted certificate so you won't get a pop up from Windows security

## Examples 
<p align="center">
<img width="450" alt="Example Message Box Go Touch Grass" src="https://github.com/user-attachments/assets/914b978e-3f52-4e9a-b813-cdc0cf552ea4">
<img width="450" alt="Example Message Box Visual Studio" src="https://github.com/user-attachments/assets/b232caa7-8253-4ffc-ae72-d6725d99c152">
</p>

## Main Window
<p align="center">
<img width="700" alt="Main Window" src="https://github.com/user-attachments/assets/87ba24c2-1005-426f-bba0-bb7122e9b5e9">
</p>

## How to Compile
Requires .NET 9.0, but no other external dependencies or nuget packages.

1. Open the solution file (`TaskDialogGenerator.sln`) in Visual Studio 2022.
2. Choose the build configuration (either `Release` or `Debug`).
3. Compile by going to `Build` > `Build Solution` or, if in `Debug` configuration, `Debug` > `Start Debugging`.
