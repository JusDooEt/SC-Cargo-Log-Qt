# SC-Cargo-Log w/ QtCreator
## About
This program aims to become an application that can be used to aid cargo haulers in the game Star Citizen. The app will log cargo routes and all the materials bought and sold throughout the routes and display the information in a readable way to the user. It will also be able to calculate the total profit earned from the cargo route.
### Motive
As a self proclaimed space trucker in Star Citizen, there are many features missing from the game that I feel are required to give the best experience to all players taking on the Space trucker role. This program will make profits more readable and later be able to track trends and route efficiency in order to give all the data to each user to create the most profitable routes and cargo types.


## Current build
![build-imageV1-3](https://github.com/JusDooEt/SC-Cargo-Log-Qt/assets/152052216/001d59e6-afd1-4992-9d07-7d4876171d57)

https://github.com/JusDooEt/SC-Cargo-Log-Qt/assets/152052216/3e01f509-da42-48ab-b288-e7e315172ace



## Current Functionality
- User balance
  - Starting balance will be read and stored whenever the value in the spinbox changes
  - Current balance will also be updated to match the starting balance if the begin route button has not been pressed and the timer has not been started.
- Ships
  - The user will use a ComboBox module to select from a list of commonly used cargo ships defined in shipList.txt
    - The Ship List class will initialize a vector of ships from a text file. That vector is then used to view and manipulate ship data.
  - The ship name label above the cargo hold will be updated whenever a ship is selected from the combo box.
  - The ship inventory labels will be updated whenever a ship is selected from the combo box.
- Cargo
  - Buy Button
    - Cargo name, price per unit, amount, and value will be read in and stored in a new dynamic Cargo object and added to the cargoHold vector.
    - A string describing the cargo purchased will be output to the Cargo Hold text edit box
    - Will verify if the value and amount is viable based on the cargo capacity and starting balance input before the route was started
      - If the purchase is not valid a dialog box will appear to warn the user and a cargo object will NOT be created and added to the stack;
    - Will update the current balance, current cargo amount and cargo hold value labels to correct values after buying cargo
  - Sell Button
    - The sell button will only be enabled and functional if the user double clicks an item that is in their cargo hold which is visually indicated on the right half of the program.
    - Cargo name, price per unit, amount, and value will be read in and stored in a new dynamic CargoSold object.
    - The values will be sent to be displayed in a pop up dialog box.
      - The dialog box will show the user the amount, price, and profit of the cargo that is being sold
      - The user can either confirm or deny the sale
      - Confirming the sale will adjust or delete the cargo item in the user's cargo hold. A confirmed sale will also disable the sell button in the main window.
        - The profit of the sale will be sent back to the main window and the user's current balance, and profit labels will be updated to match the input and calculated values.
        - Cargo input components like name, price and amount will be reset.
  - Sell All Button
    - This button will open a dialog window to confirm that the user wants to sell all of their cargo in storage.
      - The dialog box will ask for a total sell price and give live information about the user's current balance and profit.
      - The confirm to sell all button will be disabled until the user enters a value into the sell price text edit box.
      - The cancel button will close the dialog box without making any changes.
      - Confirming to sell all will send the profit value back to the original window and displayed until a new run is started.
        - The user's current amount and starting amount will be updated accordingly.
  - Cargo Hold Progress Bar
    - Allows the user to easily and visually understand how much inventory space they have in their ship's cargo hold.

## To-Do
- [x] Finish sell all button functionality
- [x] Finish sell button functionality
- [x] Create profit label functionality
- [ ] Create finished run stats page


