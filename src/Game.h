#include <Vector.h>

#include "Joystick.h"
#include "Display.h"
#include "Player.h"
#include "Object.h"

class Game
{
public:
    Joystick *joystick;
    Display *display;
    Player *player;

    Game();
    ~Game();

    void add_object(Object *object);
    void delete_object(Object *object);
    void update_draw_objects(const double delta);

private:
    /// @brief Objects are drawn and updated every frame
    Vector<Object *> objects;
};
