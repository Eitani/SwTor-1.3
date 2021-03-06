#pragma once

#include <Logic/Session.h>
#include <Network/Server.h>
#include <Network/Connection.h>
#include <System/EventListener.h>
#include <System/DBWorkQueue.h>
#include <Game/World.h>

namespace Swtor
{
	namespace Logic
	{
		class World
			: public System::EventListener, private boost::noncopyable
		{
		public:

			/**
			 * Instantiate the server
			 * @param pPort The port to start the server on
			 */
			World(unsigned short pPort);

			/**
			 * Drops a player from the server, must never be called !
			 * @param pSession The session to drop from the server and world
			 */
			void Remove(Session::pointer pSession);

			/**
			 * Get the database work queue, needed to load a DAO
			 * @return the database work queue
			 */
			System::DBWorkQueue* GetDatabaseWorkQueue();

			void OnConnection(Network::Connection::pointer pConnection);

			void OnUpdate(uint32_t pDelta);

			/**
			 * Event callback, don't call it explicitly !!!!
			 */
			virtual void OnEvent(std::shared_ptr<System::Event> pEvent);

		private:

			Network::Server							mServer;

			boost::mutex							mGuard;
			std::deque<Session::pointer>			mSessions;

			Game::World								mWorld;

			std::unique_ptr<System::DBWorkQueue>	mDBWorkQueue;
			std::unique_ptr<System::WorkQueue>		mWorkQueue;

			uint32_t mId;
		};
	}
}