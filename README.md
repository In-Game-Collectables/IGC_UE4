# IGC_UE
This document is currently a work in progress.

[In Game Collectables](https://www.igc.studio/) Plugin for Unreal Engine 4.27. This plugin will capture renders spun around a target object and export out a JSON file of the relative camera transforms. It will upload the necessary files to the IGC API to process to re-create a printable mesh.

<br />

## How to use
### Step 1: Set Up
* Get your API Key from the [IGC Platform](https://platform.igc.studio/collectables)
* Attach *BP_Capturer* to target Actor
* Input your API_key into *BP_Capturer*
* Adjust *Radius* to fit whole Actor
* Read the [Best Practices](https://github.com/In-Game-Collectables/IGC_UE4#best-practices) section for the ideal set up
### Step 2: Capturing:
* Use event *Capture* in *BP_Capturer*. This will export out all needed renders/files
    * The input parameter *Async* determines if there should be a delay between captures
        * If *Async* is false, this may freeze the game up to a couple seconds depending on the dimensions of the renders
        * *Async* should NOT be used if the Target character or lighting can animate/change between frames
* Renders/files will be outputed to *PROJECTNAME/OUTPUTS/Captures/*
* The event *CaptureAndUpload* can be used to combine the steps for Capturing and Uploading
### Step 3: Uploading
* Use event *Upload Captures* in *BP_Capturer*. This will upload all images and files within *PROJECTNAME/OUTPUTS/Captures/* to the API
* The event dispatcher *onUploadFinished* will be called when the Upload finishes. It will return:
    * Succeeded: Whether the upload succeeded
    * Message: Information about if the upload succeeded or why it failed
    * QRTexture: QR Code Texture of the link to the Checkout page
    * Checkout URL to the Checkout page
### Step 4: Checkout
* Use the event dispatcher *onUploadFinished* to get either the link to the Checkout page or the Texture2D of the QR Code

<br />

## Best Practices
### Settings
* At least 100 frames at 1024x1024 should be uploaded for best quality.
### Capturing
* Test the Capturer first and make sure the output looks good before trying to use the Upload or CaptureThenUpload functions.
* Use the *Render Parameters* wihtin *BP_Capturer* to make adjustments to the final render if you would like them brighter etc.
### Model
* The character should take up as much space possible within the renders without cutting anything off.
* The model should not have any floating pieces.
* Backfaces should not be missing.
### Lighting & Materials
* Transparent materials may create artifacts within the final model so it is best not to use them if possible.
* Having an evenly lit character will give the best results. Any shadows/lighting on the mesh will be baked into the final model.
* Pure unlit materials are not recommended. The meshing process needs at least a bit of shading to figure out the depth of points within a model.
* Recommended lighting set ups:
    * Lit shaders with ambient lighting
    * Lit shaders with fixed lights around character
    * Unlit shaders with strong ambient occlusion
* Materials with high roughness and little specular are recommended.
    * Highly specular and highly metallic materials will create artifacts within the final model.
* Lighting is even more important on simple, stylized characters, as any shadows baked on are a lot more noticeable.

<p align="center">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/1bde3a22-3f1c-4ebe-8474-6d6d48db950a" width="512" height="256">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/3d1ebcc1-6054-4b0a-8d4e-32d3a91b110a" width="512" height="256">
 <p align="center">Not Ideal vs. Ideal Lighting</p>
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

<br />

## Notes
* The Capturer will render out attached Actor, the Actor's children and and *Extra Actors*
* The variable *CurrentStage* on *BP_Capturer* can be used to see if it is currently Capturing, Uploading, CheckingOut, or not doing anything.
* If the captures are not matching what is seen on screen: in BP_Capturer/SceneCaptureComponent2D, the Show Flags under Scene Capture can be edited to get the best result
    * Set the parameter bCustomizeShowFlags to true if doing so.

<p align="center">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/31d80c8a-8853-4b72-a1f9-97d984492a44" align="top">
<img src="https://github.com/In-Game-Collectables/IGC_UE4/assets/35625367/19bf56e1-661e-4e6f-99da-8ebf6c5f5396">
</p>

<br />

## Warnings
* If *Auto-Exposure* is turned on within the project, the render will not match what the viewport looks like. It will probably instead seem much dimmer.
    * Use the *Render Parameters* on *BP_Capturer* to boost the brightness of the renders in this case.

<br />

## Support
Join the [Discord](https://discord.gg/JP2fEh4cNP) for any questions, feedback or even just a chat! (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧
