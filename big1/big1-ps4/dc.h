/******************************************************************************/
/*
  Author  - icemesh
*/
/******************************************************************************/

//header format of the script files used in Uncharted Drake's Fortune PS4 ver
struct DC_Header
{
	uint32_t 			m_magic;					///< <c>0x00</c>: 0x44433030 -> DC00
	uint32_t 			m_versionNumber;				///< <c>0x04</c>: always 0x1
	uint32_t 			m_textSize;					///< <c>0x08</c>: size of the file without the header
	uint32_t 			unk;						///< <c>0x0C</c>: always 0 
	FileInfo* 			m_pFileInfo;					///< <c>0x10</c>: ptr to unk info
	uint32_t        		unk1;						///< <c>0x18</c>: always 0 
};

struct FileInfo
{
	uint64_t 			unk;						///< <c>0x00</c>: always 0x1
	uint64_t 			unk1;						///< <c>0x08</c>: always 0x0
	int64_t  			m_numExports;					///< <c>0x10</c>: number of state-scripts/symbols declared in the file 
};

struct ScriptEntry //size = 0x20
{
	StringId    			m_scriptNameSid;				///< <c>0x00</c>: StringId of the script name
	StringId    			m_scriptTypeSid;				///< <c>0x04</c>: StringId of the script type (eg igc)
	char*       			m_scriptName;					///< <c>0x08</c>: ptr to the script name 
	uint64_t    			unk;						///< <c>0x10</c>: always 0 
	ScriptInfo* 			m_pScriptInfo;    				///< <c>0x18</c>: pointer to script info
};

//unsure if this struct has more data or not..
struct ScriptInfo 
{
	StringId   			m_scriptNameSid __attribute__ ((aligned(8));	///< <c>0x00</c>: StringId of the script name (8 bytes aligned)
	char*      			m_scriptName;					///< <c>0x08</c>: ptr to the script name 
	char*           		m_unkString;					///< <c>0x10</c>: no idea maybe a label ?
	uint32_t   			unk1;						///< <c>0x18</c>: alway 0x1 ?
	int32_t    			m_trackCount;					///< <c>0x1C</c>: number of tracks in the current script
	TrackName* 			m_pTrackName; 					///< <c>0x20</c>: ptr various track names
	int64_t    			m_lambdaCount;					///< <c>0x28</c>: total lambda count in the current script file 
	Lambda*    			m_pLambdas;					///< <c>0x30</c>: ptr to the lambda table
	uint64_t 			unk2;						///< <c>0x38</c>: always 0 ?
	ScriptLambda**			m_pScriptLambda;				///< <c>0x40</c>: ptr ptr to a scriptLambda. The second pointer can be NULL ...
	uint64_t 			unk3;						///< <c>0x48</c>: always 0 ?
	StringId*       		m_unkSid;					///< <c>0x50</c>: always points to SID("String")
};

struct TrackName //size = 0x10
{
	StringId 			m_trackNameSid __attribute__((aligned(8));	///< <c>0x00</c>: StringId of the track name (8 bytes aligned)
	char*    			m_pTrackname;					///< <c>0x08</c>: ptr to the track name 
};

struct Lambda //size = 0x28
{
	StringId 			m_blockNameSid __attribute__((aligned(8)); 	///< <c>0x00</c>: StringId of the block name (8 bytes aligned)
	char* 	 			m_pBlockName;					///< <c>0x08</c>: ptr to the block name
	ScriptLambda* 			m_pScriptLambda;				///< <c>0x10</c>: ptr to the scriptLambda
	uint64_t 			unk;						///< <c>0x18</c>: always 0 ?
	uint64_t 			unk1;						///< <c>0x20</c>: always 0 ?
};

struct ScriptLambda //0x10
{
	uint8_t*  			m_pCode;					///< <c>0x00</c>: ptr to the start of the opcode of the current block
	StringId* 			m_pSymbols;					///< <c>0x08</c>: ptr to the symbols table of the current lambda
};

//header format for a script embedded in -ingame.pak file.  
struct DC_Header
{
	uint32_t 	   		m_magic;					///< <c>0x00</c>: magic 0x44433030 -> DC00
	uint32_t 	   		m_versionNumber;				///< <c>0x04</c>: always 0x1
	uint32_t 	   		unk;						///< <c>0x08</c>: always 0 
	uint32_t 	   		unk1;						///< <c>0x0C</c>: always 0 
	ScriptLambda*  			m_pScriptLambda;				///< <c>0x10</c>: always ptr to the script lambda
};
