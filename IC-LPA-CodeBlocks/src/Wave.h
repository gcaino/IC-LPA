#ifndef WAVE_H
#define WAVE_H
// -----------------------------------------
#include "Constants.h"
#include "Enemy.h"
// -----------------------------------------
namespace lpa
{
    class Wave
    {
    private:
        Enemy  _enemies[Constants::ENEMY_MAX];

    public:
        Wave();
        ~Wave();

    };
}
#endif // WAVE_H
