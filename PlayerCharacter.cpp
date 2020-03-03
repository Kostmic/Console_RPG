

#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter(std::string name, int maxHp, int ac) : Character{name, maxHp, ac} {
}

PlayerCharacter::PlayerCharacter(std::string name, int maxHp) : Character{name, maxHp} {

}