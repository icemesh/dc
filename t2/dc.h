/******************************************************************************/
/*
  Author  - icemesh
*/
/******************************************************************************/

//t2 .dc format
namespace DC
{
	union Variant 
	{
		I8		m_I8;
		U8		m_U8;
		I16		m_I16;
		U16		m_U16;
		U16		m_F16;
		I32		m_I32;
		U32		m_U32;
		float	m_F32;
		double	m_F64;
		I64		m_I64;
		U64		m_U64;
	};
}

struct Entry;
struct ScriptInfo;
struct SsOptions;
struct SsDeclarationList;
struct SsVariable;
struct SsState;
struct SsTrack;
struct SsTrackLambda;
struct Sslambda;
struct SsOnBlock;

struct DC_Header
{
	U32						m_magic;				///< <c>0x00</c>: magic 0x44433030 -> DC00
	U32						m_versionNumber;		///< <c>0x04</c>: always 0x1
	U32						m_textSize;				///< <c>0x08</c>: size from 0x0C to (0xC+m_TextSize)
	U32						unk;					///< <c>0x0C</c>: always 0 
	U32						unk1;					///< <c>0x10</c>: always 1
	U32						m_numEntries;			///< <c>0x14</c>: num of entries
	Entry*					m_pStartOfData;			///< <c>0x18</c>: ptr to the start of data/state script //Entry*
};

struct Entry //0x18
{
	StringId64				m_scriptSid;			///< <c>0x00</c>: StringId64 of the script name: eg SID("ss-asoria-test-interactions") -> #750F7687D65AD24E
	StringId64				m_scriptTypeSid;		///< <c>0x08</c>: StringId64 of the script type: eg SID("state-script") -> #CE1173292ADCBD6E
	ScriptInfo*				m_pScriptInfo;			///< <c>0x10</c>: ptr to ScriptInfo;
};

struct ScriptInfo
{
	StringId64				m_scriptSid;			///< <c>0x00</c>: StringId64 of the script name: eg SID("ss-asoria-test-interactions") -> #750F7687D65AD24E
	SsDeclarationList*		m_pDeclList;			///< <c>0x08</c>: ptr to the declaration list
	StringId64				m_initialStateSid;		///< <c>0x10</c>: StringId64 of the initial state ?
	SsOptions*				m_pSsOptions;			///< <c>0x18</c>: ptr to the SsOption table; 
	U64						m_padding;				///< <c>0x20</c>: always 0
	SsState*				m_pSsStateTable;		///< <c>0x28</c>: ptr to the SsState Table
	//start of debug info
	I16						m_numDeclarations;		///< <c>0x30</c>: number of declarations/variables stored/declared in the script
	I16						m_line;					///< <c>0x32</c>: this is a line number thats get displayed in the debug display
	U32						m_padding1;				///< <c>0x34</c>: padding probably
	char*					m_pFileName;			///< <c>0x38</c>: the debug filename eg: t2/src/game/scriptx/ss-test/ss-test-asoria/ss-asoria-test-interactions.dcx
	U8						m_padding2[0x10];		///< <c>0x40</c>: always 0x0
};

struct SsDeclarationList //size: 0x10
{
	U32						m_unk;					///< <c>0x00</c>: 
	U32						m_numDeclarations;		///< <c>0x04</c>: numDeclarations maybe ? verify..
	SsVariable*				m_pVariableTable;		///< <c>0x08</c>: 
};

struct SsVariable //size: 0x30      
{
	StringId64				m_nameSid;				///< <c>0x00</c>: StringId of the variable name
	U64						m_padding;				///< <c>0x08</c>: always 0 ?
	StringId64				m_typeSid;				///< <c>0x10</c>: StringId of the variable type eg: SID("boolean"), SID("int32") ...
	U64						m_unk;					///< <c>0x18</c>: no idea; 
	DC::Variant*			m_pValue;				///< <c>0x20</c>: ptr to the value of the var ->
	U64						m_unk2;					///< <c>0x28</c>: no idea; 
};

/*TODO*/
struct SsOptions //size 0x58 <- binsize realstruct probably is 0x50 !!!UNSURE!!!!!!
{
	U64						m_ssOptionsSid;		/// this is only visible to the compiler table starts @ 0x8
	//paddinData
	StringId64*				m_pSymbolArray; 					//0x18
};

struct SsState //size 0x18
{
	StringId64				m_stateNameSid;			///< <c>0x00</c>: sid of the state name
	I32 					m_numTracks;			///< <c>0x08</c>: numTracks
	U32 					m_unk2;					///< <c>0x0C</c>: 
	SsOnBlock*				m_pSsOnBlock;			///< <c>0x10</c>: point to the SsOnBlock
};

struct SsOnBlock //size 0x48 || compiler size 0x50-> SID("array") 0x8 -> SsTrack, SsTrack1, etc..
{
	U32 					m_unkNumber;			///< <c>0x00</c>: 
	U64 					m_unk1;					///< <c>0x04</c>: 
	U64 					m_unk2;					///< <c>0x0C</c>:
	U16 					m_unkNumber2;			///< <c>0x18</c>:
	U16 					m_unkNumber3;			///< <c>0x1A</c>: numTracks in this block maybe
	U32 					m_unk3;					///< <c>0x1C</c>:
	SsTrack*				m_pSsTrack;				///< <c>0x20</c>: points to the track or array of tracks
	char*					m_debugBlockInfo;		///< <c>0x28</c>: debug info eg: ss-asoria-test-interactions already-complete (on ((start)))
	U8						m_padding[0x18];		///< <c>0x30</c>: either padding or reserved for future uses
};

struct SsTrack //size 0x18
{
	StringId64 				m_trackNameSid;			///< <c>0x00</c>: StringId64 of the track name
	U16 					m_unk;					///< <c>0x08</c>: always 0x0;
	I16 					m_numScriptLambdas;		///< <c>0x0A</c>: num of lambdas in the track
	U32 					m_padding;				///< <c>0x0C</c>: 
	SsTrackLambda*			m_pTrackLambda;			///< <c>0x1C</c>: 
};

struct SsTrackLambda
{
	Sslambda*				m_pLambda;				///< <c>0x00</c>: ptr to the ScriptLambda
	U64		 				m_unk;					///< <c>0x08</c>: unk value maybe size ?
};

struct Sslambda	//size 0x50 || 0x40
{
	U8*						m_pOpcode;				///< <c>0x00</c>: ptr to the block to execute
	DC::Variant*			m_pSymbols;				///< <c>0x08</c>: ptr to the array of symbols. Floats, integers stringIds etc..
	StringId64				m_funcTypeSid; 			///< <c>0x10</c>: StringId of the function type usually SID("function")
	U64						m_unk;					///< <c>0x18</c>: unk number;
	U64						m_unk2;					///< <c>0x20</c>: always 0x0 ?
	U64						m_unk3;					///< <c>0x28</c>: always 0x0 ?
	U32						m_unk4;					///< <c>0x30</c>: always 0x0 ?
	U32						m_unk5;					///< <c>0x34</c>: always 0x0 ?
	U64						m_unk6;					///< <c>0x38</c>: always -1
};
