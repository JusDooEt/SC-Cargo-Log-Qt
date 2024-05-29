# SC-Cargo-Log w/ QtCreator
## Newest Update
- Ship list initialization
  - The list of ships that is displayed in the combo box in the application is now initialized using data from the SC-Log database 'ships' table.
  - The data is no longer read from text files and has a more sophisticated and secure method of saving and reinitializing data.
  - The ship object was also given an ID member variable for future use of other tables and using the ID as a foreign key.
    - This will make the data much more organized and easier to manipulate rather than using text files.
  - Benefits
    - This will overall make our program more efficient because inserting and removing one instance of data requires a simple SQL query rather than having to rewrite the entire text file.
    - This also makes the code more readable and easier to modify in future use since we no longer need to deal with the jankiness of fstream and data types can more clearly be defined.

## About
This program aims to become an application that can be used to aid cargo haulers in the game Star Citizen. The app will log cargo routes and all the materials bought and sold throughout the routes and display the information in a readable way to the user. It will also be able to calculate the total profit earned from the cargo route.
### Motive
As a self proclaimed space trucker in Star Citizen, there are many features missing from the game that I feel are required to give the best experience to all players taking on the Space trucker role. This program will make profits more readable and later be able to track trends and route efficiency in order to give all the data to each user to create the most profitable routes and cargo types.



## Current build
<!-- [![res/images/build-imageV1.PNG](https://github.com/JusDooEt/SC-Cargo-Log-Qt/blob/master/res/images/build-imageV1-2.PNG)](https://www.youtube.com/watch?v=5nPhlwM65tE) -->
![image](https://github.com/JusDooEt/SC-Cargo-Log-Qt/assets/152052216/75224936-9c34-49d3-9ec3-1c9cd6ec8b9e)

![gif](https://media3.giphy.com/media/v1.Y2lkPTc5MGI3NjExcXh0bGwxNGEyeWFtcHI1bDNtb3ZtbjRvOXR3aGFsZXMzZ2xuZ3c1OSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/rCrJ0tjiDNU8UVZgLW/giphy.gif)

## SQLite Database (SC-Log.db)
This database includes six tables and the structure is shown in the image below. It is used to store the user's information, ship information, trade routes, transactions, locations, and trade commodities.

![SC Trade Log DB](https://github.com/JusDooEt/SC-Cargo-Log-Qt/assets/152052216/77cb4dbe-2205-48ba-9f0a-e90ee4dfedf2)

<details>
  <summary>SQL code to create the database</summary>

  ```
--
-- File generated with SQLiteStudio v3.4.4 on Fri May 17 14:44:15 2024
--
-- Text encoding used: System
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: items
CREATE TABLE IF NOT EXISTS items (
    itemID INTEGER PRIMARY KEY AUTOINCREMENT
                   UNIQUE
                   NOT NULL,
    name   TEXT    NOT NULL
                   UNIQUE
);


-- Table: locations
CREATE TABLE IF NOT EXISTS locations (
    locationID INTEGER PRIMARY KEY AUTOINCREMENT
                       NOT NULL
                       UNIQUE,
    system     TEXT    NOT NULL,
    planet     TEXT    NOT NULL,
    body       TEXT    NOT NULL,
    station    TEXT    NOT NULL
);


-- Table: routes
CREATE TABLE IF NOT EXISTS routes (
    routeID         INTEGER PRIMARY KEY AUTOINCREMENT
                            UNIQUE
                            NOT NULL,
    userID          INTEGER REFERENCES users (userID) 
                            NOT NULL,
    shipID          INTEGER REFERENCES ships (shipID) 
                            NOT NULL,
    startingBalance REAL    NOT NULL,
    finalBalance    REAL    NOT NULL,
    profit          REAL,
    date            TEXT    NOT NULL,
    time            TEXT    NOT NULL,
    duration        TEXT    NOT NULL
);


-- Table: ships
CREATE TABLE IF NOT EXISTS ships (
    shipID   INTEGER PRIMARY KEY ASC AUTOINCREMENT
                     UNIQUE
                     NOT NULL,
    make     TEXT    NOT NULL,
    model    TEXT    NOT NULL,
    capacity INTEGER NOT NULL,
    class    TEXT    NOT NULL
);

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      1,
                      'Aegis',
                      'Titan',
                      8,
                      'S'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      2,
                      'Consolidated Outland',
                      'Nomad',
                      24,
                      'S'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      3,
                      'Crusader',
                      'C2 Hercules Starlifter',
                      696,
                      'L'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      4,
                      'Crusader',
                      'M2 Hercules Starlifter',
                      522,
                      'L'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      5,
                      'Crusader',
                      'Mercury Star Runner',
                      114,
                      'M'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      6,
                      'Drake',
                      'Caterpillar',
                      576,
                      'L'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      7,
                      'Drake',
                      'Caterpillar BIS',
                      576,
                      'L'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      8,
                      'Drake',
                      'Caterpillar Pirate',
                      564,
                      'L'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      9,
                      'Drake',
                      'Cutter',
                      4,
                      'S'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      10,
                      'Drake',
                      'Cutless Black',
                      46,
                      'M'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      11,
                      'Drake',
                      'Cutless Black BIS',
                      46,
                      'M'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      12,
                      'MISC',
                      'Freelancer',
                      66,
                      'M'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      13,
                      'MISC',
                      'Freelancer MAX',
                      120,
                      'M'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      14,
                      'MISC',
                      'Hull A',
                      64,
                      'M'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      15,
                      'MISC',
                      'Hull B',
                      384,
                      'M'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      16,
                      'MISC',
                      'Hull C',
                      4608,
                      'L'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      17,
                      'MISC',
                      'Reliant Kore',
                      6,
                      'S'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      18,
                      'RSI',
                      'Aurora CL',
                      6,
                      'S'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      19,
                      'RSI',
                      'Constellation Andromeda',
                      96,
                      'M'
                  );

INSERT INTO ships (
                      shipID,
                      make,
                      model,
                      capacity,
                      class
                  )
                  VALUES (
                      20,
                      'RSI',
                      'Constellation Taurus',
                      174,
                      'M'
                  );


-- Table: transactions
CREATE TABLE IF NOT EXISTS transactions (
    transactionID INTEGER PRIMARY KEY AUTOINCREMENT
                          NOT NULL
                          UNIQUE,
    routeID       INTEGER REFERENCES routes (routeID) 
                          NOT NULL,
    locationID    INTEGER NOT NULL
                          REFERENCES locations (locationID),
    itemID        INTEGER REFERENCES items (itemID) 
                          NOT NULL,
    quantity      INTEGER NOT NULL,
    price         REAL    NOT NULL,
    time          TEXT    NOT NULL
                          UNIQUE,
    sold          INTEGER NOT NULL
                          CONSTRAINT [Boolean Check] CHECK (sold >= 0 & sold < 2) 
);


-- Table: users
CREATE TABLE IF NOT EXISTS users (
    userID   INTEGER PRIMARY KEY
                     UNIQUE
                     NOT NULL,
    email    TEXT    UNIQUE,
    username TEXT    UNIQUE
                     NOT NULL,
    password TEXT    NOT NULL
);


COMMIT TRANSACTION;
PRAGMA foreign_keys = on;

  ```
</details>

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
  - The Ship Selection combo box in the top left of the program can now be sorted by the user using two buttons representing sorting the list by name or by cargo capacity
    - The Quick Sort algorithm was used to sort the ships.
      - The algorithm was modified in order to work with the Ship type object.
      - The algorithm also allows the programmer to choose which ship member to sort by using an enum flag, either 'CARGO' or 'NAME'.
## To-Do
- [x] Finish sell all button functionality
- [x] Finish sell button functionality
- [x] Create profit label functionality
- [x] Created Ship list sort functionality
- [ ] Create finished run stats page
- [ ] Create individual buttons for different commodities instead of having the user type in the name
- [ ] Add functionality to the database.
  - [x] Initialize shipList from the database.
  - [ ] trade routes get added to DB
  - [ ] transactions get added to DB
- [ ] Create a login and register page for the program.
  - [ ] Adds registered users to the database.
  - [ ] uses the database to verify login credentials 
- [ ] Create a window allowing users to see their past routes.
  - [ ] Add functionality to allow users to sort by day using a calendar widget.
  - [ ] Selecting a route will show the user all of the transactions and further details of the route.



