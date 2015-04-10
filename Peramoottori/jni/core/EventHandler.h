#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <android_native_app_glue.h>
#include <android/sensor.h>

namespace pm
{
	/// Handles input and event processing.

	class EventHandler
	{

		friend class android_native_app_glue;
		friend class Application;
		friend class Game;

	private:

		EventHandler() : accelerometerSensor(nullptr),
			hasAccelerometer(false),
			sensorEventQueue(nullptr) {};

		void Initialize(android_app* application);

		void EnableSensors();

		void DisableSensors();

		~EventHandler();

		// Pointer to const data does not allow modification of the data through the pointer.
		const ASensor* accelerometerSensor; ///< Sensor that measures proper acceleration.
		bool hasAccelerometer; ///< Does device have accelerometer.

		// Contains sensor events in queue.
		// Returns negative value if no events are available or error has occurred
		ASensorEventQueue* sensorEventQueue; ///< Sensor event queue.

	protected:

		/// Handles application input processing.
		/// Reference given to android_native_app_glue.
		static int HandleInput(android_app* application, AInputEvent* event);

		/// Handles application command processing.
		/// Reference given to android_native_app_glue.
		static void ProcessCommand(android_app* application, int32_t command);
	};
}

#endif