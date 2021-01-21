#include <array>
#include <vector>
#include <SDL2/SDL_events.h>

#include "input.h"

namespace pxr
{
namespace input
{

static std::array<KeyLog, KEY_COUNT> keys;   // logs for all keys.
static std::vector<KeyCode> history;         // ordered history of keys pressed.

static KeyCode convertSdlKeyCode(int sdlCode)
{
  switch(sdlCode) {
    case SDLK_a: return KEY_a;
    case SDLK_b: return KEY_b;
    case SDLK_c: return KEY_c;
    case SDLK_d: return KEY_d;
    case SDLK_e: return KEY_e;
    case SDLK_f: return KEY_f;
    case SDLK_g: return KEY_g;
    case SDLK_h: return KEY_h;
    case SDLK_i: return KEY_i;
    case SDLK_j: return KEY_j;
    case SDLK_k: return KEY_k;
    case SDLK_l: return KEY_l;
    case SDLK_m: return KEY_m;
    case SDLK_n: return KEY_n;
    case SDLK_o: return KEY_o;
    case SDLK_p: return KEY_p;
    case SDLK_q: return KEY_q;
    case SDLK_r: return KEY_r;
    case SDLK_s: return KEY_s;
    case SDLK_t: return KEY_t;
    case SDLK_u: return KEY_u;
    case SDLK_v: return KEY_v;
    case SDLK_w: return KEY_w;
    case SDLK_x: return KEY_x;
    case SDLK_y: return KEY_y;
    case SDLK_z: return KEY_z;
    case SDLK_SPACE: return KEY_SPACE;
    case SDLK_BACKSPACE: return KEY_BACKSPACE;
    case SDLK_RETURN: return KEY_ENTER;
    case SDLK_LEFT: return KEY_LEFT;
    case SDLK_RIGHT: return KEY_RIGHT;
    case SDLK_DOWN: return KEY_DOWN;
    case SDLK_UP: return KEY_UP;
    default: return KEY_COUNT;
  }
}

void initialize()
{
  for(auto& key : keys)
    key._isDown = key._isReleased = key._isPressed = false;
}

void Input::onKeyEvent(const SDL_Event& event)
{
  assert(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP);

  KeyCode key = convertSdlKeyCode(event.key.keysym.sym);

  if(key == KEY_COUNT) 
    return;

  if(event.type == SDL_KEYDOWN){
    keys[key]._isDown = true;
    keys[key]._isPressed = true;
    history.push_back(key);
  }
  else{
    keys[key]._isDown = false;
    keys[key]._isReleased = true;
  }
}

void Input::onUpdate()
{
  for(auto& key : keys)
    key._isPressed = key._isReleased = false;
  history.clear();
}

bool isKeyDown(KeyCode key)
{
  return keys[key]._isDown;
}

bool isKeyPressed(KeyCode key)
{
  return keys[key]._isPressed;
}

bool isKeyReleased(KeyCode key)
{
  return keys[key]._isReleased;
}

const std::vector<KeyCode>& getHistory()
{
  return history;
}

int Input::keyToAsciiCode(KeyCode key)
{
  switch(key){
    case KEY_a: return 'a';
    case KEY_b: return 'b';
    case KEY_c: return 'c';
    case KEY_d: return 'd';
    case KEY_e: return 'e';
    case KEY_f: return 'f';
    case KEY_g: return 'g';
    case KEY_h: return 'h';
    case KEY_i: return 'i';
    case KEY_j: return 'j';
    case KEY_k: return 'k';
    case KEY_l: return 'l';
    case KEY_m: return 'm';
    case KEY_n: return 'n';
    case KEY_o: return 'o';
    case KEY_p: return 'p';
    case KEY_q: return 'q';
    case KEY_r: return 'r';
    case KEY_s: return 's';
    case KEY_t: return 't';
    case KEY_u: return 'u';
    case KEY_v: return 'v';
    case KEY_w: return 'w';
    case KEY_x: return 'x';
    case KEY_y: return 'y';
    case KEY_z: return 'z';
    case KEY_SPACE: return ' ';
    default: return -1;
  }
}

} // namespace input
} // namespace pxr
