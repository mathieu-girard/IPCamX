May 2013 - Mathieu Girard

IPCamX is an ActiveX component dedicated to deliver images grabbed from an IP camera stream. Delivered stream can be used into LabVIEW or with OpenCV. Or wherever you want since you modify the component :)

Installation:
- Download VLC
- Set VLC_PLUGIN_PATH into environment variable to VLC plugins directory
- Install OpenCV for Windows (according to the right version of Visual Studio)
- Compile 3rd parties module from OpenCV with CMake if needed
- Generate lib from libvlc.dll : http://wiki.videolan.org/GenerateLibFromDll.
- Others source here : http://code.google.com/p/msinttypes/

Use:
- Under Demo\Demo IE.htm for testing into Internet Explorer
- Under Demo\LabVIEW\ for testing into LabVIEW (you can choose to use or not Vision Development Module)