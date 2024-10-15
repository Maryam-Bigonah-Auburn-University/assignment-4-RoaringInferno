#include <iostream>
#include <string>
#include <vector>

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
    std::cin >> command;

    // Split string by spaces
    std::vector<std::string> tokens;
    std::string token;
    for (char c : command)
    {
      if (c == ' ')
      {
        tokens.push_back(token);
        token = "";
      }
      else
      {
        token += c;
      }
    }

    // Define token pop
    const auto pop_token = [&tokens]() -> std::string
    {
      std::string token = tokens[0];
      tokens.erase(tokens.begin());
      return token;
    };

    // The first token is the command name, remove it
    std::string commandName = pop_token();

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
    enum class CommandHash
    {
      NEW = 2,
      DELETE = 0,
      SHOW = 3,
      QUIT = 1
    } commandID = static_cast<CommandHash>((commandName[0] | 28) - 124);

    // Execute the command
    switch (commandID)
    {
      case CommandHash::NEW:
      {
        // Get the score value
        const int score = std::stoi(pop_token());
        // The token list now contains only the names

        // Add the players
        while(players.size() < 10 && !tokens.empty()) // While there is space in the players vector
        {
          players.push_back(Player(score, pop_token()));
        }
        if (!tokens.empty()) // If there are still names to add (meaning the maximum number of players was reached)
        {
          std::cout << "Warning: Maximum number of players reached.\n";
        }
        break;
      } // CommandHash::NEW
      case CommandHash::DELETE:
      {
        // Delete the players
        while (!tokens.empty())
        {
          const std::string name = pop_token();
          // Find the player with the given name
          for (std::vector<Player>::size_type i = 0; i < players.size(); i++)
          {
            bool deleted = false;
            if (players[i].getName() == name)
            {
              players.erase(players.begin() + i);
              deleted = true;
              break;
            }
            if (!deleted) // If the name is not one of the players
            {
              std::cout << "Warning: Player not found: " << name << "\n";
            }
          }
        }
        break;
      } // CommandHash::DELETE
      case CommandHash::SHOW:
      {
        const auto display_player = [](const Player& player)
        {
          std::cout << player.getName() << " " << player.getScore() << "\n";
        };

        // Show the players
        if (tokens.empty()) // If no names are given
        {
          for (Player player : players)
          {
            display_player(player);
          }
        }
        else // If names are given
        {
          while (!tokens.empty())
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
      } // CommandHash::SHOW
      case CommandHash::QUIT:
      {
        return 0;
      } // CommandHash::QUIT
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