#pragma once

struct Options {
	bool enableMirrors = true;
	bool enableShadows = true;
	bool enableDiffuse = true;
	bool enableAmbient = true;
	bool enableSpecular = true;

	void ToggleMirrors() { enableMirrors = !enableMirrors; }
	void ToggleShadows() { enableShadows = !enableShadows; }
	void ToggleDiffuse() { enableDiffuse = !enableDiffuse; }
	void ToggleAmbient() { enableAmbient = !enableAmbient; }
	void ToggleSpecular() { enableSpecular = !enableSpecular; }

	// Enable all options by default
	Options()
	{
		enableMirrors = true;
		enableShadows = true;
		enableDiffuse = true;
		enableAmbient = true;
		enableSpecular = true;
	}

	// Enable specific options
	Options(bool _mir, bool _shad, bool _diff, bool _amb, bool _spec) 
		: enableMirrors(_mir), enableShadows(_shad), enableDiffuse(_diff), enableAmbient(_amb), enableSpecular(_spec) {}
};