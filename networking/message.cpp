
#include "message.h"



Message::Message(game_state state)
{
    serialize(state);
}


void Message::serialize(game_state state)
{
    size_t i = body.size();

    body.resize(body.size() + sizeof(state));
    
}