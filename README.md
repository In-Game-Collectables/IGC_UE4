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

<p align="center">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/e0cde956-24da-406e-a4f3-b4caf6348f6e" width="256" height="256">
 <h6 align="center">Output Example</h6>
</p>


## Best Practices
* At least 100 frames at 2048x2048 should be uploaded for best quality.
* The character should take up as much space possible within the renders without cutting anything off.
* The mesh should not have any floating pieces.
* Having an evenly lit character will give the best results. Any shadows on the mesh will be baked into the final model.
* Pure unlit shaders are not recommended. The meshing process needs at least a bit of shading to figure out the depth of points within a model.
* Recommended lighting set ups:
    * Lit shaders with ambient lighting
    * Lit shaders with fixed lights around character
    * Unlit shaders with strong ambient occlusion
* Materials with high roughness and little specular are recommended.
* Highly specular and highly metallic materials will create artifacts within the final model.
* Lighting is even more important on simple, stylized characters, as any shadows baked on are a lot more noticeable on simple characters rather than detailed characters.

<p align="center">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/e018ec43-adc9-499a-93c0-48ae76b465e7" width="512" height="256">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/3025d1d8-fd54-4fff-b602-1d2a4935f81f" width="512" height="256">
 <h6 align="center">Directional Lighting vs. Evenly Shaded</h6>
</p>

### Examples
<p align="center">
 
![pigeon](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/0de3ea1d-7b58-44ab-aae1-a9b133c3b298)

![robot](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/011f8c02-86a3-467d-bde5-a02fbf65b6ba)

![mushroom](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/6c4fd85a-ff61-4e3e-ad42-46d6b329a899)

</p>

[Pigeon](https://sketchfab.com/3d-models/pigeon-quirky-series-e607ed34d37d433496d5a557c8230b28)

[Robot](https://sketchfab.com/3d-models/robot-4-b0c5f2f5ac04402dad029d6516d706b9)

[Mushroom](https://sketchfab.com/3d-models/cuute-mushroom-ffc370ddc6d542d590b9f503d0892ce0)
