/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CFont.cpp				 	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	2D & 3D Font			       *
*  Created On *	11/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#include "../Header Files/CFont.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Default constructor.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
CFont::CFont()
{
    m_pFont = NULL; 
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Initialize the font
Parameters:
[in] pDevice - D3D Device for D3DXCreateFont call
[in] faceName - Font name
[in] size - Font size
[in] bold - Bold if TRUE
[in] italic - Italicized if TRUE
Returns: TRUE if font was created successfully, FALSE otherwise.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
BOOL CFont::Initialize( LPDIRECT3DDEVICE9 pDevice, LPCWSTR faceName, int size, BOOL bold, BOOL italic )
{
    SAFE_RELEASE( m_pFont );
    HRESULT hr = 0;
    hr = D3DXCreateFont( pDevice, -size, 0, bold ? 800 : 0, 1, italic, DEFAULT_CHARSET, 
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, faceName, &m_pFont );
    if (FAILED(hr))
    {
		SHOWERROR("D3DXCreateFont() failed.", __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Print some 2D text.
Parameters:
[in] text - Text to print
[in] xPosition - X position in window coordinates
[in] yPosition - Y position in window coordinates
[in] color - Color of the text.
[in] sprite - Sprite for batch printing
[in] textBoxWidth - Width to constrain text in
[in] textBoxHeight - Height to constrain text in
[in] format - FONTALIGNMENT value.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFont::Print(LPCWSTR text, int xPosition, int yPosition, DWORD color, LPD3DXSPRITE sprite,
    int textBoxWidth, int textBoxHeight, FONTALIGNMENT alignment )
{
    if ( !m_pFont ) 
    {
        return;
    }
    DWORD format = DT_EXPANDTABS;
    if ( textBoxWidth == 0 )
    {
        format |= DT_NOCLIP;
    }
    else
    {
        format |= DT_WORDBREAK;
        switch ( alignment )
        {
        case FA_LEFT:
            format |= DT_LEFT;
            break;
        case FA_CENTER:
            format |= DT_CENTER;
            break;
        case FA_RIGHT:
            format |= DT_RIGHT;
            break;
        case FA_TOPRIGHT:
            format |= DT_RIGHT | DT_TOP;
            break;
        case FA_BOTTOMRIGHT:
            format |= DT_RIGHT | DT_BOTTOM;
            break;
        case FA_TOPLEFT:
            format |= DT_LEFT | DT_TOP;
            break;
        case FA_BOTTOMLEFT:
            format |= DT_LEFT | DT_BOTTOM;
            break;
        }
        if ( textBoxHeight == 0 )
        {
            // A width is specified, but not a height.
            // Make it seem like height is infinite
            textBoxHeight = 2000;
        }
    }
    RECT rect = { xPosition, yPosition, xPosition + textBoxWidth, yPosition + textBoxHeight };
    m_pFont->DrawText( sprite, text, -1, &rect, format, color );
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Releases video resources. Call whenever the device is lost or before reseting the device.
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFont::OnLostDevice()
{
    if ( m_pFont )
    {
        m_pFont->OnLostDevice();
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Re-acquire video resources. Call after device is reset
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFont::OnResetDevice()
{
    if ( m_pFont )
    {
        m_pFont->OnResetDevice();
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
Summary: Release interfaces
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void CFont::Release()
{
    SAFE_RELEASE( m_pFont ); 
}