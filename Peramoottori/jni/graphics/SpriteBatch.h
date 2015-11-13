#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "Batch.h"
#include <GLES2\gl2.h>
#include <scene\GameEntity.h>
#include <vector>
#include <graphics\Text.h>

namespace pm
{
	/** \brief Keeps track of Drawable GameEntity objects that have been queued to be drawn and optimizes rendering.
	*
	* \ingroup Graphics
	*/

	class SpriteBatch
	{
	public:

		/** \brief Return instance of SpriteBatch. 
		* \return Pointer to SpriteBatch.
		*/
		static SpriteBatch* GetInstance();

		/** \brief Delete pm::SpriteBatch and all associated resources.
		*
		* Deleting pm::SpriteBatch is already part of cleaning routine when application is shut down permanently.
		* As such user will no need to call this unless for very specific reason.
		*/
		void DestroyInstance();

		/** \brief Render all objects that have been queued to be drawn.
		*
		* \sa AddGameEntity(), AddtranslucentGameEntity() and AddText().
		*/
		void Draw();

		void DrawOld();

		/** @name Batching Functions
		* \brief Store GameEntity objects to be drawn.
		*/
		///@{
		/** \param[in] gameEntity Pointer to GameEntity object. */
		void AddOpaqueGameEntity(GameEntity* gameEntity);

		/** \brief Add GameEntity object that contains transparency.
		* \param[in] gameEntity Pointer to GameEntity object.
		*/
		void AddTranslucentGameEntity(GameEntity* gameEntity);

		/** \brief Add std::vector of GameEntity objects that contains transparency.
		* \param[in] entityVector Pointer to std::vector<GameEntity*>.
		*/
		void AddOpaqueGameEntity(std::vector<GameEntity*> entityVector);
		
		/** \brief Add Text object that contains transparency.
		* \param[in] textEntity Pointer to pm::Text object.
		*/
		void AddText(Text* textEntity);
		///@}

	private:

		SpriteBatch() { Layers.resize(11); opaqueLayerBatchVector.resize(11); translucentLayerBatchVector.resize(11); }; ///< Neccessary for singleton.

		~SpriteBatch() {}; ///< Can't be deleted without calling DestroyInstance.

		bool IsDrawable(GameEntity* gameEntity); ///< Check if GameEntity is drawable.
		
		void CreateLayers();
		
		void BatchLayerComponents(int layer, bool type);

		void BatchAllLayers();

		void BatchOpaqueComponents();///< Makes final translucent batch.

		void BatchTranslucentComponents();///< Makes final translucent batch.


		void ParseData(GameEntity* gameEntity, // GameEntity is gutted to form data matrises that can be assimilated into Batch.
			std::vector<GLfloat>* vertexData, 
			std::vector<GLushort>* indexData,
			glm::mat4* transformMatrix,
			GLuint* textureIndex);

		std::vector<GameEntity*> opaqueGameEntityVector;
		std::vector<GameEntity*> translucentGameEntityVector;
		std::vector<Batch> batchVector; ///< Contains all batched draw data.
		
		std::vector<std::vector<Batch>> opaqueLayerBatchVector;// Info for all layers, separated by layer. size 11, opaque first, translucent secound
		std::vector<std::vector<Batch>> translucentLayerBatchVector;
		static SpriteBatch* instance;

		struct Layer
		{
			std::vector<GameEntity*> translucentGO;
			std::vector<GameEntity*> opaqueGO;
		};
		std::vector<Layer> Layers;
	};
}

#endif