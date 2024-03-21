# SC-Cargo-Log w/ QtCreator
## About
This program aims to become an application that can be used to aid cargo haulers in the game Star Citizen. The app will log cargo routes and all the materials bought and sold throughout the routes and display the information in a readable way to the user. It will also be able to calculate the total profit earned from the cargo route.
### Motive
As a self proclaimed space trucker in Star Citizen, there are many features missing from the game that I feel are required to give the best experience to all players taking on the Space trucker role. This program will make profits more readable and later be able to track trends and route efficiency in order to give all the data to each user to create the most profitable routes and cargo types.


## Current build
![build-imageV1](res/images/build-imageV1.PNG)

![giphy](https://github.com/JusDooEt/SC-Cargo-Log/assets/152052216/41f1e77c-f780-4e51-979f-ad950c02c79a)

## Current Functionality
- User balance
  - Starting balance will be read and stored whenever the value in the spinbox changes
  - Current balance will also be updated to match the starting balance if the begin route button has not been pressed and the timer has not been started.
- Ships
  - The program will read in a ship name entered by the user in the corresponding line edit text box
    - This name is default set to “Crusader, C2 Hercules Starlifter” on app start for testing purposes and as an example
    - The class variable where the name is stored will be updated every time the user hits the return key while the line edit text box is selected and in focus
  - The program will read and record the ship cargo capacity input by the user in the corresponding spinbox
    - This value is set to 696 by default on app start to make it align with the default ship name
    - The cargoCap value in the spinBox will also update the label below the cargo hold list box to match with the input value
- Cargo
  - Buy Button
    - Cargo name, price per unit, amount, and value will be read in and stored in a new dynamic Cargo object and added to the cargo stack. The top of the stack is declared in the widget class.
    - A string describing the cargo purchased will be output to the Cargo Hold text edit box
    - Will verify if the value and amount is viable based on the cargo capacity and starting balance input before the route was started
      - If the purchase is not valid a dialog box will appear to warn the user and a cargo object will NOT be created and added to the stack;
    - Will update the current balance, current cargo amount and cargo hold value labels to correct values after buying cargo

## To-Do
- [ ] Finish sell all button functionality
- [ ] Finish sell button functionality
- [ ] Create profit label functionality
- [ ] Create finished run stats page


