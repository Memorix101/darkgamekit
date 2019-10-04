
// Dark GDK - The Game Creators - www.thegamecreators.com

// include Dark GDK header file
#include <DarkGameKit.h>

// Array for finer asteroid data
float ast [ 100 ];
// Backdrop shift
float	shiftx	=	0.0f;
float	sya		=	0.0f;
float	sy		=	0.0f;
float	a		=	0.0f;
float	s		=	0.0f;
float	sss		=	0.0f;
float	g		=	0.0f;
float	h		=	0.0f;
int		t		=	0;


// main entry point for program
void DarkGDK ( void )
{
//	dbSetDir ( "media\\" );

	dbSyncOn   ( );
	dbSyncRate ( 60 );

	// Standard Setup Code for all examples
//	dbColorBackdrop ( 0 );

	// Load images
	dbSetImageColorKey		( 255 , 0 , 255 );
	dbCreateAnimatedSprite	( 1 , "animspr.png" , 4 , 4 , 16 );
	dbLoadImage				( "ship.png" , 2 );
	dbLoadImage				( "backdrop.jpg" , 3 );

	// Setup backdrop sprite
	dbSprite			( 1001 , 0 , 0 , 3 );
	dbSprite			( 1002 , 0 , 0 , 3 );
	dbSetSpritePriority ( 1001 , 0 );
	dbSetSpritePriority ( 1002 , 0 );
	dbSizeSprite		( 1001 , 1024 , 1024 );
	dbSizeSprite		( 1002 , 1024 , 1024 );

	// Setup asteroid sprite
	dbSprite		( 1 , 320 , 240 , 16 );
	dbSizeSprite	( 1 , 128 , 128 );
	dbOffsetSprite	( 1 , 64 , 64 );

	// Copy animating sprite
	for ( t=2 ; t < 100 ; t++ )
	{
		 dbCloneSprite		( 1 , t );
		 dbSprite			( t , dbRND ( 640 + 256 ) - 128 , dbRND ( 1400 ) - 400 , 16 );
		 ast [ t ]			= ( float ) dbSpriteY ( t );
		 dbRotateSprite		( t , ( float ) dbRND ( 350 ) );
		 dbSetSpriteFrame	( t , dbRND ( 15 ) );
		 dbSetSprite		( t , 0 , 1 );

		 a		= ( float ) dbRND ( 350 );
		 s		= 32.0f;
		 sss	= 64.0f +	( dbCOS ( a ) * s );
		 dbSizeSprite	( t , ( int ) sss , ( int ) sss );
		 dbOffsetSprite	( t , ( int ) sss / 2 , ( int ) sss / 2 );
		 if ( t < 50 )
		 {
			dbSetSpritePriority ( t , 1 );
		 }
		 else
		 {
			dbSetSpritePriority ( t , 3 );
		 }
	}

	// Setup ship sprite
	dbSprite ( 100 , 200 , 140 , 2 );
	dbSetSpritePriority ( 100 , 2 );

	dbDrawSpritesFirst ( );

	// loop until the escape key is pressed
	while ( LoopGDK ( ) )
	{
	//	if ( dbEscapeKey ( ) )
	//		return;

/*		 char szFPS [ 256 ] = "";
		strcpy ( szFPS, "fps = " );
		strcat ( szFPS, dbStr ( dbScreenFPS ( ) ) );
		dbText ( dbScreenWidth ( ) - 20 - dbTextWidth ( szFPS ), dbScreenHeight ( ) - 40, szFPS );*/

		 // Move backdrop
		 shiftx += 2.0f;
		 sya = dbWrapValue ( sya + 0.1f );
		 sy = -260 + ( dbCOS ( sya ) * 260 );
		 if ( shiftx > 1024.0f ) shiftx -= 1024.0f;
		 dbSprite ( 1001 , 0 - ( int ) shiftx , ( int ) sy , 3 );
		 dbSprite ( 1002 , 1024 - ( int ) shiftx , ( int ) sy , 3 );
		 
		 // Control sprite auto-animation
		 for ( t = 1 ; t < 100 ; t++ )
		 {
			  a = dbWrapValue	( dbSpriteAngle ( t ) + 1 + dbRND( 2 ) );
			  dbRotateSprite	( t , 90 );
			  dbMoveSprite		( t , -3.0f );
			  ast [ t ] = ast [ t ] - ( dbSIN ( sya ) * 0.3f );

			  if ( dbSpriteX ( t ) < -128 )
			  {
				    dbMoveSprite ( t , ( 640 + 256 ) );
					a = ( float ) dbRND ( 350 );
			  }

			  dbSprite ( t , dbSpriteX ( t ) , ( int ) ast [ t ] , dbSpriteImage ( t ) );
			  dbPlaySprite ( t , 1 , 16 , 50 );
			  dbRotateSprite ( t , a );
			  
		 }		 

		 // Glide ship
		 g = dbWrapValue ( g + 1 );
		 h = dbWrapValue ( h + 0.5f );
		 dbSprite ( 100 , 200 , 140 + ( int ) ( dbSIN ( g ) * 10 ) , 2 );
		 dbScaleSprite ( 100 , 100 + dbSIN ( h ) * 20.0f );
		 dbRotateSprite ( 100 , dbSIN ( sya ) * 10.0f );		

		 dbSync ( );
	}
}

int main(void)
{
	StartGDK();
	DarkGDK();
	return 0;
}