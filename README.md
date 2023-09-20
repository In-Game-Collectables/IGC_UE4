# IGC_UE
This document is currently a work in progress.
 
Plugin build for Unreal Engine 4.27. This plugin will capture renders spun around a target object and export out a JSON file of the relative camera transforms. It will upload the necessary files to the IGC API to process to re-create a printable mesh.

## How to use
### Step 1: Set Up
* Get your API Key from the [IGC Platform](https://platform.igc.studio/collectables)
* Attach *BP_Capturer* to target Actor
* Input your API_key into *BP_Capturer*
* Adjust *Radius* to fit whole Actor
* The Capturer will be centered on the Actor's pivot point.
### Step 2: Capturing:
* Use event *Capture Renders* in *BP_Capturer*. This will export out all needed renders/files. This may freeze the game up to a couple seconds depending on the dimensions of the renders.
* Renders/files will be outputed to *PROJECTNAME/OUTPUTS/Captures/*
### Step 3: Uploading
* Use event *Upload Captures* in *BP_Capturer*. This will upload all images and files within *PROJECTNAME/OUTPUTS/Captures/* to the API
* The API will return a URL to the checkout page after the upload is complete
### Step 4: Checkout
* *BP_CaptureUploader* has an empty event *UseQRCode* which is given a Texture2D parameter of a QR Code leading to the API's checkout page when everything is finished


<br />
### Parameters
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
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/9e6035e0-48d5-4040-927e-9dccc46c11f6" width="256" height="256">
 <p align="center">Output Example</p>
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
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/7e9cc2ff-6b6d-4bad-ad04-623516f5c90f" width="512" height="256">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/c0c76996-15bb-43bb-b677-d2165eb56a15" width="512" height="256">
 <p align="center">Directional Lighting vs. Evenly Shaded</p>
</p>

### Ideal Lighting Examples
<p align="center">

![pigeon](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/13398085-397f-43d2-8756-01e94a8c5d3d)

![robot](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/51be5bf6-64f0-45fa-85ec-996c11f8b183)

![mushroom](https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/1604f6ef-7124-40d0-9a0d-7403ae29ded6)

</p>

[Pigeon](https://sketchfab.com/3d-models/pigeon-quirky-series-e607ed34d37d433496d5a557c8230b28)

[Robot](https://sketchfab.com/3d-models/robot-4-b0c5f2f5ac04402dad029d6516d706b9)

[Mushroom](https://sketchfab.com/3d-models/cuute-mushroom-ffc370ddc6d542d590b9f503d0892ce0)
