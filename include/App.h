#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "SplashState.h"

class App
{
	public:
		void					run();
		static App*				getApp();

        sf::RenderWindow		mWindow;
        sf::View                mView;

    private:
        static App*             app;
        App();

        void                    manageEvents();
        void                    update(sf::Time elapsedTime);
        void                    render();

    private:
        static const sf::Time	minUpdateTime;

        sf::Clock               generalClock;
        sf::Clock               updateClock;
        sf::Time                updateStart;
        sf::Time                lastUpdateTime;

};

#endif
