# SC-Cargo-Log w/ QtCreator
## Newest Update
- The Ship Selection combo box in the top left of the program can now be sorted by the user using two buttons representing sorting the list by name or by cargo capacity
  - The Quick Sort algorithm was used to sort the ships.
    - The algorithm was modified in order to work with the Ship type object.
    - The algorithm also allows the programmer to choose which ship member to sort by using an enum flag, either 'CARGO' or 'NAME'.  
## About
This program aims to become an application that can be used to aid cargo haulers in the game Star Citizen. The app will log cargo routes and all the materials bought and sold throughout the routes and display the information in a readable way to the user. It will also be able to calculate the total profit earned from the cargo route.
### Motive
As a self proclaimed space trucker in Star Citizen, there are many features missing from the game that I feel are required to give the best experience to all players taking on the Space trucker role. This program will make profits more readable and later be able to track trends and route efficiency in order to give all the data to each user to create the most profitable routes and cargo types.


## Current build
<!-- [![res/images/build-imageV1.PNG](https://github.com/JusDooEt/SC-Cargo-Log-Qt/blob/master/res/images/build-imageV1-2.PNG)](https://www.youtube.com/watch?v=5nPhlwM65tE) -->
![image](https://github.com/JusDooEt/SC-Cargo-Log-Qt/assets/152052216/75224936-9c34-49d3-9ec3-1c9cd6ec8b9e)

![gif](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExcXh0bGwxNGEyeWFtcHI1bDNtb3ZtbjRvOXR3aGFsZXMzZ2xuZ3c1OSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/rCrJ0tjiDNU8UVZgLW/giphy.gif)


## Current Functionality
- User balance
  - Starting balance will be read and stored whenever the value in the spinbox changes
  - Current balance will also be updated to match the starting balance if the begin route button has not been pressed and the timer has not been started.
- Ships
  - The program reads from a .txt file in order to initialize the list of ships the user can choose from.
  - The list of ships will be displayed to the user using a combo box.
  - The combo box selection will be used to manipulate the list and make sure the correct ship is selected for the trade run.
  - The list of ships can be sorted in ascending order by either their name or cargo capacity.
    - The sorting will change the vector or ship pointer and then refresh the combo box to correlate with the newly sorted list.
    - The [Quick Sort](https://github.com/JusDooEt/Ship-Sorting) algorithm is used to sort the vector of ship pointers.
      - This algorithm has been modified to allow it to compare members of the Ship struct.
      - The programmer can change the member being compared using an ENUM flag during the quickSort function call. (Flags: CARGO, NAME)
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
  - Cargo Hold Progress Bar
    - Allows the user to easily and visually understand how much inventory space they have in their ship's cargo hold.

## To-Do
- [x] Finish sell all button functionality
- [x] Finish sell button functionality
- [x] Create profit label functionality
- [x] Created Ship list sort functionality
- [ ] Create finished run stats page


