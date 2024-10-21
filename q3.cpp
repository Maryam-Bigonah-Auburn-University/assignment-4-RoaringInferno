#include <iostream>
#include <string>
#include <vector>
#include <queue>

// #define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x) std::cout << x << std::endl
#else
#define DEBUG_PRINT(x)
#endif

class Player
{
 private:
   std::string name;
   int score;
 public:
   Player(); // 0-initializes the score and name. The name is considered an invalid value at this time.
   Player(int newScore, const std::string& newname); // Changed the parameter to const reference to avoid copying.
   void setName(const std::string& newName); // Changed the parameter to const reference to avoid copying.
   void setScore(int newScore);
   std::string getName() const; // Member is valid for const qualifier, so I added it.
   int getScore() const; // Member is valid for const qualifier, so I added it.
};

int main()
{
  /**
   * A better data structure for this problem would be a hash table.
   */
  std::vector<Player> players(10);

  // Initialize the players
  for (std::vector<Player>::size_type i = 0; i < players.size(); i++)
  {
    players[i] = Player(0, "player" + std::to_string(i));
  }

  while (true)
  {
    std::cout << "> ";
    std::string command;
    std::getline(std::cin, command);

    // Split string by spaces
    std::vector<std::string> tokens;
    std::string token;
    for (char c : command)
    {
      if (c == ' ')
      {
        if (token != "")
        {
          tokens.push_back(token);
          token = "";
        }
      }
      else
      {
        token += c;
      }
    }
    if (token != "") tokens.push_back(token);
    DEBUG_PRINT("String split");

    // Define token pop
    std::vector<std::string>::iterator it = tokens.begin();
    const std::vector<std::string>::iterator it_end = tokens.end();
    const auto pop_token = [&it]() -> std::string
    {
      std::string retval = *it;
      it++;
      return retval;
    };
    const auto has_token = [&it, &it_end]() -> bool
    {
      return it != it_end;
    };
    DEBUG_PRINT("Token pop defined");

    // The first token is the command name, remove it
    std::string commandName = pop_token();
    DEBUG_PRINT("Command name: " << commandName);

    // Hash across the possible command names
    /**
     * <required> - Required argument
     * [optional] - Optional argument
     * <...> - One or more arguments
     * [...] - Zero or more arguments
     * 
     * 1. "new" <score> <names...> - Create a new player with the given score and names. If the maximum number of players is reached, a warning is printed and following players are not added.
     * 2. "delete" <name...> - Delete the player(s) with the given name.
     * 3. "show" [name...] - Print all players and their scores. If a names are given, print only their information instead.
     * 4. "quit" - Exit the program.
     * 
     * Hash with function ([0] | 28):
     * 1. new     : 126 - 124 = 2
     * 2. delete  : 124 - 124 = 0
     * 3. show    : 127 - 124 = 3
     * 4. quit    : 125 - 124 = 1
     */
    enum class CommandID
    {
      NEW = 2,
      DELETE = 0,
      SHOW = 3,
      QUIT = 1
    } commandID = static_cast<CommandID>((commandName[0] | 28) - 124);
    DEBUG_PRINT("CommandID" << std::to_string(static_cast<int>(commandID)));
    switch (commandID)
    {
      case CommandID::NEW:
        DEBUG_PRINT("Executing new");
        break;
      case CommandID::DELETE:
        DEBUG_PRINT("Executing delete");
        break;
      case CommandID::SHOW:
        DEBUG_PRINT("Executing show");
        break;
      case CommandID::QUIT:
        DEBUG_PRINT("Executing quit");
        break;
      default:
        std::cout << "Invalid command.\n";
        continue;
    }

    // Execute the command
    switch (commandID)
    {
      case CommandID::NEW:
      {
        // Get the score value
        const int score = std::stoi(pop_token());
        // The token list now contains only the names

        // Add the players
        while(players.size() < 10 && has_token()) // While there is space in the players vector
        {
          const std::string name = pop_token();
          std::cout << "Adding player: \"" << name << "\" with score " << score << "\n";
          players.push_back(Player(score, name));
        }
        if (has_token()) // If there are still names to add (meaning the maximum number of players was reached)
        {
          std::cout << "Warning: Maximum number of players reached.\n";
        }
        break;
      } // CommandID::NEW
      case CommandID::DELETE:
      {
        if (!has_token()) // If no names are given
        {
          std::cout << "Warning: No names given.\n";
          break;
        }
        // Delete the players
        while (has_token())
        {
          const std::string name = pop_token();
          // Find the player with the given name
          for (std::vector<Player>::size_type i = 0; i < players.size(); i++)
          {
            bool deleted = false;
            if (players[i].getName() == name)
            {
              std::cout << "Deleting player: \"" << name << "\"\n";
              players.erase(players.begin() + i);
              deleted = true;
              break;
            }
            if (!deleted) // If the name is not one of the players
            {
              std::cout << "Warning: Player not found: " << name << "\n";
              while (has_token())
              {
                std::cout << "Discarding: " << pop_token() << "\n";
              }
            }
          }
        }
        break;
      } // CommandID::DELETE
      case CommandID::SHOW:
      {
        const auto display_player = [](const Player& player)
        {
          std::cout << "\"" << player.getName() << "\": " << std::to_string(player.getScore()) << "\n";
        };

        // Show the players
        if (!has_token()) // If no names are given
        {
          for (Player player : players)
          {
            display_player(player);
          }
        }
        else // If names are given
        {
          while (has_token())
          {
            const std::string name = pop_token();
            // Find the player with the given name
            for (Player player : players)
            {
              if (player.getName() == name)
              {
                display_player(player);
              }
            }
          }
        }
        break;
      } // CommandID::SHOW
      case CommandID::QUIT:
      {
        return 0;
      } // CommandID::QUIT
    }
  }
}


Player::Player() :
  score(0),
  name("")
{
}

Player::Player(int newScore, const std::string& newName) :
  score(newScore),
  name(newName)
{
}

void Player::setName(const std::string& newName)
{
  name = newName;
}

void Player::setScore(int newScore)
{
  score = newScore;
}

std::string Player::getName() const
{
  return name;
}

int Player::getScore() const
{
  return score;
}