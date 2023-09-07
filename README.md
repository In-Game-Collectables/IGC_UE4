# IGC_UE
 
Plugin build for Unreal Engine 4.27. This plugin will capture renders spun around a target object and export out a JSON file of the relative camera transforms. It can upload the necessary files to the IGC API to process.

## Contains
* Example Third Person Project
* IGC Plug-in within Plugins/IGC_UE

## How to use
* Attach to target Actor
* Adjust *Radius* to fit whole Actor
* Renders/files will be outputed to *PROJECTNAME/OUTPUTS/Captures/*
* The Capturer will be centered on the Actor's pivot point.

## Parameters
* Frame Count
    * Number of images to be rendered out
* Path XSpeed
    * The amount of revolutions around the Actor the camera goes
* Radius
    * Radius around the target actor the camera will go
* Camera FOV
    * Field of View of render camera
* Render Size
    * Dimensions of render width & height
* Extra Actors
    * Any extra actors that should be rendered out with the Actor
* Spawn Custom Lighting
    * If true, will spawn four point lights around Actor to attempt to even out lighting.

## Notes
* The Capturer will render out attached Actor, the Actor's children and and *Extra Actors*
* The rendered images on disk will outputted with an inverted alpha. The alpha will be flipped while it gets processed within the API.
* The transforms.json file will get reformatted with the API to work with instant-ngp.


