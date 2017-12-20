#ifndef TITLE_SCREEN_H
#define TITLE_SCREEN_H
// ----------------------------------------------------------------------------
#include "Screen.h"
// ----------------------------------------------------------------------------
namespace lpa
{
// ----------------------------------------------------------------------------
class TitleScreen : public Screen
{
public:
	TitleScreen(ScreenManager* screenManager);
	~TitleScreen();

	virtual void handleEvent(sf::Event event);
	virtual void update(sf::Time elapsedTime);
};
// ----------------------------------------------------------------------------
}
#endif // TITLE_SCREEN_H


