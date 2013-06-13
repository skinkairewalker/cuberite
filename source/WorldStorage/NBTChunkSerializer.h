
// NBTChunkSerializer.h

// Declares the cNBTChunkSerializer class that is used for saving individual chunks into NBT format used by Anvil





#pragma once

#include "../ChunkDef.h"





// fwd:
class cFastNBTWriter;
class cEntity;
class cBlockEntity;
class cChestEntity;
class cDispenserEntity;
class cDropperEntity;
class cFurnaceEntity;
class cHopperEntity;
class cJukeboxEntity;
class cNoteEntity;
class cSignEntity;
class cFallingBlock;
class cMinecart;
class cMinecartWithChest;
class cMinecartWithFurnace;
class cMonster;
class cPickup;
class cItemGrid;





class cNBTChunkSerializer :
	public cChunkDataSeparateCollector
{
public:
	cChunkDef::BiomeMap m_Biomes;
	unsigned char m_VanillaBiomes[cChunkDef::Width * cChunkDef::Width];
	bool m_BiomesAreValid;


	cNBTChunkSerializer(cFastNBTWriter & a_Writer);

	/// Close NBT tags that we've opened
	void Finish(void);
	
	bool IsLightValid(void) const {return m_IsLightValid; }

protected:
	
	/* From cChunkDataSeparateCollector we inherit:
	- m_BlockTypes[]
	- m_BlockMetas[]
	- m_BlockLight[]
	- m_BlockSkyLight[]
	*/
	
	cFastNBTWriter & m_Writer;
	
	bool m_IsTagOpen;  // True if a tag has been opened in the callbacks and not yet closed.
	bool m_HasHadEntity;  // True if any Entity has already been received and processed
	bool m_HasHadBlockEntity;  // True if any BlockEntity has already been received and processed
	bool m_IsLightValid;  // True if the chunk lighting is valid


	/// Writes an item into the writer, if slot >= 0, adds the Slot tag. The compound is named as requested.
	void AddItem(const cItem & a_Item, int a_Slot, const AString & a_CompoundName = "");
	
	/// Writes an item grid into the writer; begins the stored slot numbers with a_BeginSlotNum
	void AddItemGrid(const cItemGrid & a_Grid, int a_BeginSlotNum = 0);
	
	// Block entities:
	void AddBasicTileEntity(cBlockEntity *     a_Entity, const char * a_EntityTypeID);
	void AddChestEntity    (cChestEntity *     a_Entity);
	void AddDispenserEntity(cDispenserEntity * a_Entity);
	void AddDropperEntity  (cDropperEntity *   a_Entity);
	void AddFurnaceEntity  (cFurnaceEntity *   a_Furnace);
	void AddHopperEntity   (cHopperEntity *    a_Entity);
	void AddJukeboxEntity  (cJukeboxEntity *   a_Jukebox);
	void AddNoteEntity     (cNoteEntity *      a_Note);
	void AddSignEntity     (cSignEntity *      a_Sign);
	
	// Entities:
	void AddBasicEntity       (cEntity * a_Entity, const AString & a_ClassName);
	void AddFallingBlockEntity(cFallingBlock * a_FallingBlock);
	void AddMinecartEntity    (cMinecart * a_Minecart);
	void AddMonsterEntity     (cMonster * a_Monster);
	void AddPickupEntity      (cPickup * a_Pickup);
	
	void AddMinecartChestContents(cMinecartWithChest * a_Minecart);
	
	// cChunkDataSeparateCollector overrides:
	virtual bool LightIsValid(bool a_IsLightValid) override;
	virtual void BiomeData(const cChunkDef::BiomeMap * a_BiomeMap) override;
	virtual void Entity(cEntity * a_Entity) override;
	virtual void BlockEntity(cBlockEntity * a_Entity) override;
} ;  // class cNBTChunkSerializer




