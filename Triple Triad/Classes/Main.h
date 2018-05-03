#ifndef MAIN_H
#define MAIN_H

namespace TT
{
	enum class FileID
	{
		//Font
		FontSegoeUIBold,
		FontTahoma,
		FontTimesNewRomanBold,
		FontTimesNewRomanBoldItalic,
		FontAlgerian,

		//Texture
		TextureBackground,
		TextureInterface,
		TextureWindow,
		TextureCardBackFace,
		TextureCardsLevel01,
		TextureCardsLevel02,
		TextureCardsLevel03,
		TextureCardsLevel04,
		TextureCardsLevel05,
		TextureCardsLevel06,
		TextureCardsLevel07,
		TextureCardsLevel08,
		TextureCardsLevel09,
		TextureCardsLevel10,
		TextureSquaresoftLogo,

		//Music
		MusicMainTheme,

		//Sound
		SoundCursorMove,
		SoundCursorCancel,
		SoundCursorError,
		SoundDrawCard,
		SoundTurnCard,
		SoundRandomPlayerTurn,

		//Data
		VertexShader,
		PixelShader,
	};
}

#endif