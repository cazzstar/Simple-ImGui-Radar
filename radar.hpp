	inline ImVec2 RadarPosition;

void CalculatePointOnRadar( FVector vOrigin, int& screenx, int& screeny )
{
	FVector vAngle = Camera::Rotation;
	auto fYaw = vAngle.y * M_PI / 180.0f;
	float dx = vOrigin.x - Camera::Location.x;
	float dy = vOrigin.y - Camera::Location.y;

	float fsin_yaw = sinf( fYaw );
	float fminus_cos_yaw = -cosf( fYaw );

	float x = dy * fminus_cos_yaw + dx * fsin_yaw;
	x = -x;
	float y = dx * fminus_cos_yaw - dy * fsin_yaw;

	float range = ( float )( functions::RadarDistance / 5 ) * 1000.f;

	RadarRange( &x, &y, range );

	ImVec2 DrawPos = ImVec2( Cached::RadarPosition.x + ( functions::RadarSize / 2 ), Cached::RadarPosition.y + ( functions::RadarSize / 2 ) );
	ImVec2 DrawSize = ImVec2( functions::RadarSize, functions::RadarSize );

	float radarRadius = functions::RadarSize / 2;

	float distance = sqrt( pow( screenx - DrawPos.x, 2 ) + pow( screeny - DrawPos.y, 2 ) );

	if ( distance > radarRadius )
	{
		float angle = atan2( screeny - DrawPos.y, screenx - DrawPos.x );
		screenx = static_cast< int >( DrawPos.x + radarRadius * cos( angle ) );
		screeny = static_cast< int >( DrawPos.y + radarRadius * sin( angle ) );
	}

	int rad_x = ( int )DrawPos.x;
	int rad_y = ( int )DrawPos.y;

	float r_siz_x = DrawSize.x;
	float r_siz_y = DrawSize.y;

	int x_max = ( int )r_siz_x + rad_x - 5;
	int y_max = ( int )r_siz_y + rad_y - 5;

	screenx = rad_x + ( ( int )r_siz_x / 2 + int( x / range * r_siz_x ) );
	screeny = rad_y + ( ( int )r_siz_y / 2 + int( y / range * r_siz_y ) );

	if ( screenx > x_max )
		screenx = x_max;

	if ( screenx < rad_x )
		screenx = rad_x;

	if ( screeny > y_max )
		screeny = y_max;

	if ( screeny < rad_y )
		screeny = rad_y;
}
auto AddToRadar( FVector WorldLocation, bool bIsVisible, int Distance ) -> void
{
	static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
	ImGui::Begin( ( "##radar" ), nullptr, flags );

	int ScreenX, ScreenY = 0;
	ImDrawList* ImGui::GetWindowDrawList( ); = ImGui::GetWindowDrawList( );

	CalculatePointOnRadar( WorldLocation, ScreenX, ScreenY );

	switch ( bIsVisible )
	{
	case true:
		ImGui::GetWindowDrawList( );->AddCircleFilled( ImVec2( ScreenX, ScreenY ), 3, ImColor( 255, 50, 50, 75 ), 64 );
		ImGui::GetWindowDrawList( );->AddCircleFilled( ImVec2( ScreenX, ScreenY ), 1, ImColor( 255, 50, 50 ), 64 );
		break;
	case false:
		ImGui::GetWindowDrawList( );->AddCircleFilled( ImVec2( ScreenX, ScreenY ), 3, ImColor( 255, 255, 255, 75 ), 64 );
		ImGui::GetWindowDrawList( );->AddCircleFilled( ImVec2( ScreenX, ScreenY ), 1, ImColor( 255, 255, 255 ), 64 );
		break;
	}

	ImGui::End( );
}

		if ( functions::radar )
			AddToRadar( vRoot, IsVisible, fDistance ); // vRoot -> Bottom |  auto fDistance = vHead.Distance( Camera::Location ) / 100.f;
