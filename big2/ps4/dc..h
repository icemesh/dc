#pragma once
/******************************************************************************/
/*
  Author  - icemesh
*/
/******************************************************************************/
#include <stdint.h>

struct ScriptFile;
struct ScriptFileEntry;
struct StateScript;
struct SsDeclarationList;
struct SsDeclaration;
struct SsOptions;
struct SsState;
struct SsOnBlock;
struct SsTrackGroup;
struct SsTrack;
struct SsLambda;
struct ScriptLambda;

typedef uint32_t StringId;

struct DC_Header
{
	uint32_t				m_magic;				///< <c>0x00</c>: magic 0x44433030 -> DC00
	uint32_t				m_versionNumber;		///< <c>0x04</c>: always 0x1
	uint32_t				m_textSize;				///< <c>0x08</c>: size from 0x0C to (0xC+m_TextSize)
	uint32_t				unk;					///< <c>0x0C</c>: always 0 
	ScriptFile*				m_pScriptFile;			///< <c>0x10</c>: ptr to the script file
	uint32_t				m_padding;				///< <c>0x18</c>: padding probably
};

struct ScriptFileEntry
{
	StringId				m_scriptId;				///< <c>0x00</c>: string id of the script name	
	uint32_t				m_unk;					///< <c>0x04</c>: this is probably padding
	StateScript*			m_pStateScript;			///< <c>0x08</c>: ptr to the script id
};

struct ScriptFile
{
	uint32_t				m_unk;					///< <c>0x00</c>: always 0x1 ?
	int32_t					m_numScriptEntries;		///< <c>0x0x4</c>: number of script entries in the file
	ScriptFileEntry			m_aEntries[];			///< <c>0x0x8</c>: variable sized array of ScriptFileEntry entries
};

struct StateScript //0x3C
{
	StringId				m_stateScriptId;		///< <c>0x00</c>: StringId of the script name 
	uint32_t				m_sidPadding;			///< <c>0x04</c>: this is probably padding
	SsDeclarationList*		m_pSsDeclList;			///< <c>0x08</c>: always 0 ?
	StringId				m_initialStateId;		///< <c>0x10</c>: StringId of the name of the initial state
	uint32_t				m_sidPadding2;			///< <c>0x14</c>: this is probably padding
	uint64_t				m_unk2;					///< <c>0x18</c>: always 0 ?
	SsOptions*				m_pSsOptions;			///< <c>0x20</c>: ptr to the SsOptions
	int32_t					m_numStates;			///< <c>0x28</c>: number of states 
	uint32_t				m_unk3;					///< <c>0x2C</c>: always 0 ? 
	SsState*				m_pSsStateTable;		///< <c>0x28</c>:  ptr to the state table
	uint32_t				m_padding;				///< <c>0x28</c>: padding probably
};

struct SsOptions
{
	uint64_t				m_unkNumber;			///< <c>0x00</c>: always 0x4 ?
	const char*				m_unkName;				///< <c>0x08</c>: does this always point to a string?
	uint32_t				m_unkNumber2;			///< <c>0x10</c>: 
	uint8_t					m_imLazy[0x10];			///< <c>0x14</c>: always 0?
};

struct SsState //0x10
{
	StringId				m_stateId;				///< <c>0x00</c>: StringId of the state name
	int32_t					m_numSsOnBlock;			///< <c>0x04</c>: number of SsOnBlocks UNSURE
	SsOnBlock*				m_pSsOnBlock;			///< <c>0x08</c>: ptr to the block table
};

struct SsOnBlock //0x1C ?
{
	int32_t					m_blockType;			///< <c>0x00</c>: 00 -> on begin || 01 -> on end || 02 -> on <customName> || 03 -> on update
	StringId				m_blockEventId;			///< <c>0x04</c>: StringId of the event name. Only present if the type is 0x2
	uint64_t				m_unk;					///< <c>0x08</c>: always 0 ?
	SsTrackGroup*			m_pTrackGroup;			///< <c>0x10</c>: ptr to the track group
	//uint32_t				m_padding; not sure if its always present or not
};

struct SsTrackGroup //0x14
{
	int32_t					m_numTracks;			///< <c>0x00</c>: number of tracks probably
	SsTrack*				m_pTracks;				///< <c>0x04</c>: ptr to the tracks table
	uint32_t				m_padding;				///< <c>0x10</c>: padding probably
};

struct SsTrack //0x14
{
	StringId				m_trackId;				///< <c>0x00</c>: StringId of the track name
	int32_t					m_totalLambdaCount;		///< <c>0x04</c>: number of entries in the table
	SsLambda*				m_pSsLambdaTable;		///< <c>0x08</c>: ptr to the SsLambda table
	uint32_t				m_padding;				///< <c>0x10</c>: padding probably
};

struct SsLambda //0x14
{
	uint64_t				m_unk;					///< <c>0x00</c>: always 0 ?
	ScriptLambda*			m_pScriptLambda;		///< <c>0x08</c>: ptr to the script lambda
	uint32_t				m_padding;				///< <c>0x10</c>: padding probably
};

struct ScriptLambda //0x1C
{
	uint8_t*				m_pOpcode;				///< <c>0x00</c>: ptr to the block of code to execute
	uint32_t*				m_pSymbolTable;			///< <c>0x08</c>: ptr to the symbols table
	StringId				m_typeId;				///< <c>0x10</c>: StringId of the type eg: SID("function")
	uint32_t				m_sidPadding;			///< <c>0x14</c>: string id padding
	uint32_t				m_padding;				///< <c>0x18</c>: padding probably
};

struct SsDeclarationList //0x14
{
	int32_t					m_numDeclarations;		///< <c>0x00</c>: number of declarations 
	uint32_t				m_padding;				///< <c>0x04</c>: padding probably
	SsDeclaration*			m_pDeclarations;		///< <c>0x08</c>: ptr to the list of declarations
	uint32_t				m_padding2;				///< <c>0x04</c>: padding probably
};

struct SsDeclaration //0x18
{
	StringId				m_declId;				///< <c>0x00</c>: StringId of the declaration name
	StringId				m_declTypeId;			///< <c>0x04</c>: StringId of the declaration type eg: boolean, int32 etc..
	int16_t					m_unk;					///< <c>0x08</c>: unk number
	int16_t					m_isVar;				///< <c>0x0A</c>: is variable ? // TODO: CHECK
	uint32_t				unk3;					///< <c>0x0C</c>: always 0 ?
	void*					m_pDeclValue;			///< <c>0x10</c>: ptr to the declaration value
};