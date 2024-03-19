# SC-Cargo-Log w/ QtCreator
## About
This program aims to become an application that can be used to aid cargo haulers in the game Star Citizen. The app will log cargo routes and all the materials bought and sold throughout the routes and display the information in a readable way to the user. It will also be able to calculate the total profit earned from the cargo route.
### Motive
As a self proclaimed space trucker in Star Citizen, there are many features missing from the game that I feel are required to give the best experience to all players taking on the Space trucker role. This program will make profits more readable and later be able to track trends and route efficiency in order to give all the data to each user to create the most profitable routes and cargo types.


## Current build
[![res/images/build-imageV1.PNG](https://github.com/JusDooEt/SC-Cargo-Log-Qt/blob/master/res/images/build-imageV1-2.PNG)](https://www.youtube.com/watch?v=5nPhlwM65tE)
![gif](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExcXh0bGwxNGEyeWFtcHI1bDNtb3ZtbjRvOXR3aGFsZXMzZ2xuZ3c1OSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/rCrJ0tjiDNU8UVZgLW/giphy.gif)


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
  - Sell All Button
    - This button will open a dialog window to confirm that the user wants to sell all of their cargo in storage.
      - The dialog box will ask for a total sell price and give live information about the user's current balance and profit.
      - The confirm to sell all button will be disabled until the user enters a value into the sell price text edit box.
      - The cancel button will close the dialog box without making any changes.
      - Confirming to sell all will send the profit value back to the original window and displayed until a new run is started.
        - The user's current amount and starting amount will be updated accordingly.

## To-Do
- [x] Finish sell all button functionality
- [ ] Finish sell button functionality
- [x] Create profit label functionality
- [ ] Create finished run stats page


