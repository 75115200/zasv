#ifndef C_AUDIO_BASE_CFG_H
#define C_AUDIO_BASE_CFG_H

class CabCfg
{
public:
	int		Init	( char* cfg_file );
	void	Uinit	( );	

	int getVb		( );
	int getVshift	( );

private:
	int m_vb;
	int m_vshift;
};

#endif

