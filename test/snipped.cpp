
	dbSyncOn ( );
	dbSyncRate ( 60 );
	dbCreateAnimatedSprite ( 1, "animatedsprite.png", 4, 4, 1 );

	while ( LoopGDK ( ) )
	{
		dbPasteSprite ( 1, 0, 0 );
		dbPlaySprite ( 1, 1, 16, 200 );
		dbSync ( );
	}

	// return back to windows
	return;