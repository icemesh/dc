/******************************************************************************/
/*
  Author  - icemesh
*/
/******************************************************************************/
#pragma once
#include <stdint.h>

struct SsDeclarationList;
struct SsDeclaration;
struct StateScript;
struct SsOptions;
struct SymbolArray;
struct SsState;
struct SsTrackGroup;
struct SsOnBlock;
struct SsTrack;
struct SsLambda;
struct ScriptLambda;

typedef uint32_t StringId;

struct Entry;

struct DC_Header //0x1C
{
	uint32_t				m_magic;				///< <c>0x00</c>: magic 0x44433030 -> DC00
	uint32_t				m_versionNumber;		///< <c>0x04</c>: always 0x1
	uint32_t				m_textSize;				///< <c>0x08</c>: size from 0x0C to (0xC+m_TextSize)
	uint32_t				unk;					///< <c>0x0C</c>: always 0 
	uint32_t				unk1;					///< <c>0x10</c>: always 1
	int32_t					m_numEntries;			///< <c>0x14</c>: num of entries
	Entry*					m_pStartOfData;			///< <c>0x18</c>: ptr to the start of data/state script(s) 
};

struct Entry //0x0C
{
	StringId				m_scriptId;				///< <c>0x00</c>: StringId of the script name
	StringId				m_typeId;				///< <c>0x04</c>: StringId of the script type eg SID("state-script")
	void*					m_entryPtr;				///< <c>0x08</c>: ptr to the scriptType cast this to the IdGroup || StateScript etc..
};

struct StateScript //0x2C
{
	StringId				m_stateScriptId;		///< <c>0x00</c>: StringId of the script name 
	SsDeclarationList*		m_pSsDeclList;			///< <c>0x04</c>: ptr to the ss-decl-list
	StringId				m_initialStateId;		///< <c>0x08</c>: StringId of the name of the initial state
	SsOptions*				m_pSsOptions;			///< <c>0x0C</c>: ptr to the SsOptions
	uint64_t				unk2;					///< <c>0x10</c>: always 0 ?
	SsState*				m_pSsStateTable;		///< <c>0x18</c>: ptr to the SsState Table
	int16_t					m_numStates;			///< <c>0x1C</c>: number of states
	//start of debug info
	int16_t					m_line;					///< <c>0x1E</c>: this is a line number thats get displayed in the debug display
	const char*				m_pDebugFileName;		///< <c>0x20</c>: the debug filename 
	const char*				m_pErrorName;			///< <c>0x24</c>: used to store any error if any TODO: Verify
	uint32_t				m_padding;				///< <c>0x28</c>:
};

struct SsDeclarationList //0x10 
{
	int32_t					m_unkNum1;				///< <c>0x00</c>: always 0 ?
	int32_t					m_numDeclarations;		///< <c>0x04</c>: number of declared vars in the table
	SsDeclaration*			m_pDeclarations;		///< <c>0x08</c>: ptr to the list of declarations
};

struct SsDeclaration //0x10
{
	StringId				m_declId;				///< <c>0x00</c>: StringId of the declaration name
	StringId				m_declTypeId;			///< <c>0x04</c>: StringId of the declaration type eg: boolean, int32 etc..
	int16_t					m_unk;					///< <c>0x08</c>: unk number
	int16_t					m_isVar;				///< <c>0x0A</c>: is variable ?
	void*					m_pDeclValue;			///< <c>0x0C</c>: ptr to the declaration value
};

struct SsOptions //0x24 UNSURE
{
	uint8_t					m_imLazy[0x18];			///< <c>0x00</c>: maybe always 0 maybe not
	SymbolArray*			m_pSymbolArray;			///< <c>0x18</c>: ptr to the symbol array
	int32_t					m_unkNum;				///< <c>0x1C</c>: unk Number
	uint32_t				m_unk;					///< <c>0x20</c>: always 0 ?
};

struct SymbolArray //0x08
{
	int32_t					m_numEntries;			///< <c>0x00</c>: number of entries probably
	StringId*				m_pSymbols;				///< <c>0x04</c>: ptr to symbol. TODO: check if they're all sids
};

struct SsState //0x0C
{
	StringId				m_nameId;				///< <c>0x00</c>:  StringId of the state name 
	int32_t					m_numSsOnBlocks;		///< <c>0x04</c>:  numTracks
	SsOnBlock*				m_pSsOnBlocks;			///< <c>0x08</c>:  ptr to the SsOnBlocks
};

struct SsOnBlock //size 0x20
{
	int32_t					m_blockType;			///< <c>0x00</c>:  //on start || on update || on event etc
	StringId				m_blockId;				///< <c>0x04</c>:  StringId of the block name
	void*					m_pScriptLambda;		///< <c>0x08</c>:  ptr to the script Lambda
	uint16_t				m_unk;					///< <c>0x0C</c>:  unk number
	int16_t					m_numTracks;			///< <c>0x0E</c>:  num trackss
	SsTrack*				m_pTrack;				///< <c>0x1C</c>:  ptr to a track
	const char*				m_name;					///< <c>0x14</c>:  
	uint32_t				m_unk1;					///< <c>0x18</c>:
	uint32_t				m_unk2;					///< <c>0x1C</c>:
};

struct SsTrack //0x10
{
	StringId				m_trackId;				///< <c>0x00</c>:  StringId of the track name
	uint16_t				m_unk;					///< <c>0x04</c>:  always 0?
	int16_t					m_totalLambdaCount;		///< <c>0x06</c>:  number of SsLambda present
	SsLambda*				m_pSsLambda;			///< <c>0x08</c>:  ptr to the SsLambda table
};

struct SsLambda //0x08
{
	ScriptLambda*			m_pScriptLambda;		///< <c>0x00</c>:  ptr to the script lambda of the track
	uint32_t				m_unkNumber;			///< <c>0x04</c>:  unk number maybe size ?
};

struct ScriptLambda //0x14
{
	uint8_t*				m_pOpcode;				///< <c>0x00</c>:  ptr to the first opcode of the script
	uint32_t*				m_pSymbols;				///< <c>0x04</c>:  ptr to the symbol table
	StringId                m_typeId;				///< <c>0x08</c>:  usually SID("function")
	uint32_t				m_unkNumber;			///< <c>0x0C</c>:  no idea what this is used for
	uint32_t				m_unk;					///< <c>0x10</c>:  always 0 ?
};
