# IGC_UE
This document is currently a work in progress.
 
Plugin build for Unreal Engine 4.27. This plugin will capture renders spun around a target object and export out a JSON file of the relative camera transforms. It will upload the necessary files to the IGC API to process to re-create a printable mesh.

## How to use
### Capturing:
* Attach *BP_Capturer* to target Actor
* Adjust *Radius* to fit whole Actor
* Use events *Capture Renders* in *BP_Capturer*
* Renders/files will be outputed to *PROJECTNAME/OUTPUTS/Captures/*
* The Capturer will be centered on the Actor's pivot point.
* Use event *Capture Renders* in *BP_Capturer*. This will export out all needed renders/files. This may freeze the game up to a couple seconds depending on the dimensions of the renders.
### Uploading
* Use event *Upload Captures* in *BP_Capturer*. This will upload all images and files within *PROJECTNAME/OUTPUTS/Captures/* to the API
* The API will return a URL to the checkout page after the upload is complete
* *BP_CaptureUploader* has an empty event *UseQRCode* which is given a Texture2D parameter of a QR Code leading to the API's checkout page when everything is finished

## Parameters
* Frame Count
    * Number of images to be rendered out
* Radius
    * Radius around the target actor the camera will go
* Camera FOV
    * Field of View of render camera
* Render Size
    * Dimensions of render width & height
* Extra Actors
    * Any extra actors that should be rendered out with the Actor

## Notes
* The Capturer will render out attached Actor, the Actor's children and and *Extra Actors*
* The rendered images on disk will outputted with an inverted alpha. The alpha will be flipped while it gets processed within the API.

## Best Practices
* At least 100 frames at 2048x2048 should be uploaded for best quality
* The mesh should not have any floating pieces
* Having an evenly lit character will give the best results. Any shadows on the mesh will be baked into the final model.
* Pure unlit shaders are not recommended. The meshing process needs shading to figure out the depth of points within a model.
* Recommended:
    * Lit shaders with fixed lights around character
    * Unlit shaders with strong ambient occlusion
* Highly specular materials can create artifacts within the final model
* Lighting is even more important on simple, stylized characters, as any shadows baked on are a lot more noticeable than detailed characters.

![shaded](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/71d33916-9a49-4877-a4d0-e9e998340bb1)
Un-ideal: Would have shadows baked in and model will be printed out darker compared to 

![lit](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/2a2e12b0-9354-4175-9926-84b5c4418576)
Ideal: Mostly evenly lit with rough materials.
