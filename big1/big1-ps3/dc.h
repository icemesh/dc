#pragma once
/******************************************************************************/
/*
  Author  - icemesh
*/
/******************************************************************************/

//header format of the script files used in Uncharted Drake's Fortune PS3 ver
struct DC_Header
{
	uint32_t 				m_magic;				///< <c>0x00</c>: 0x44433030 -> DC00
	uint32_t 				m_versionNumber;		///< <c>0x04</c>: always 0x1
	uint32_t 				m_textSize;				///< <c>0x08</c>: size of the file without the header
	uint32_t 				unk;					///< <c>0x0C</c>: always 0 
	ScriptFile*				m_pScriptFile;			///< <c>0x10</c>: ptr to unk info
};

struct ScriptFile
{
	uint32_t 				unk1;					///< <c>0x00</c>: always 0x1
	uint32_t 				unk2;					///< <c>0x04</c>: always 0x0
	int32_t  				m_numExports;			///< <c>0x08</c>: number of state-scripts/symbols declared in the file 
};

struct ScriptFileEntry //size = 0x14
{
	StringId    				m_scriptNameSid;	///< <c>0x00</c>: StringId of the script name
	StringId    				m_scriptTypeSid;	///< <c>0x04</c>: StringId of the script type (eg igc)
	const char*					m_scriptName;		///< <c>0x08</c>: ptr to the script name 
	uint32_t    				unk;				///< <c>0x0C</c>: always 0 
	Igc*						m_pIgc;				///< <c>0x10</c>: pointer to the igc
};

struct Igc
{
	StringId   				m_scriptNameSid; 		///< <c>0x00</c>: StringId of the script name
	const char*				m_scriptName;			///< <c>0x04</c>: ptr to the script name 
	const char*				m_unkString;			///< <c>0x08</c>: ptr to an unk string. Maybe task related ?
	uint32_t   				unk;					///< <c>0x0C</c>: alway 0x1 ?
	int32_t    				m_trackCount;			///< <c>0x10</c>: number of tracks in the current script
	TrackName*				m_pTrackName; 			///< <c>0x14</c>: ptr various track names
	int32_t    				m_lambdaCount;			///< <c>0x18</c>: total lambda count in the current script file 
	Lambda*					m_pLambdas;				///< <c>0x1C</c>: ptr to the lambda table
	uint32_t   				unk1;					///< <c>0x20</c>: alway 0x1 ?
	ScriptLambda**			m_pScriptLambda;		///< <c>0x24</c>: ptr ptr to a scriptLambda. The second pointer can be NULL
	uint32_t    			unk2;					///< <c>0x28</c>: always 0 
};

struct TrackName //size = 0x8
{
	StringId 				m_trackNameSid;			///< <c>0x00</c>: StringId of the track name
	const char*				m_pTrackname;			///< <c>0x04</c>: ptr to the track name 
};

struct Lambda //size = 0x14
{
	StringId 				m_blockNameSid; 		///< <c>0x00</c>: StringId of the block name 
	const char*				m_pBlockName;			///< <c>0x04</c>: ptr to the block name
	ScriptLambda*			m_pScriptLambda;		///< <c>0x08</c>: ptr to the scriptLambda
	uint32_t 				unk;					///< <c>0x0C</c>: always 0 ?
	uint32_t 				unk1;					///< <c>0x10</c>: always 0 ?
};

struct ScriptLambda //0x8
{
	uint8_t*				m_pCode;				///< <c>0x00</c>: ptr to the start of the opcode of the current block
	StringId*				m_pSymbols;				///< <c>0x04</c>: ptr to the symbols table of the current lambda
};


//header format for a script embedded in -ingame.pak file. 
struct DC_Header
{
	uint32_t 	   	 		m_magic;				///< <c>0x00</c>: magic 0x44433030 -> DC00
	uint32_t 	   	 		m_versionNumber;		///< <c>0x04</c>: always 0x1
	uint32_t 	   	 		m_textSize;				///< <c>0x08</c>: 0x10 to m_TextSize
	uint32_t 	   	 		unk;					///< <c>0x0C</c>: always 0 
	ScriptLambda*			m_pScriptLambda;		///< <c>0x10</c>: always 0x18 
};
