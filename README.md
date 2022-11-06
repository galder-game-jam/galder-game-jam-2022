# game-dev-template
A template for game development primarily with C++ in mind. This also includes a game design template.

# Example game (raylib_template)
- `raylib_template` contains simple code to showcase a very minimal and simple game.
- When compiled as `Debug` you also get:
  - The option to go to switch maps using the `F1` and `F2` keys.
  - Debug text via the debug manager.
- There is no fullscreen support using raylib directly in the example, but you may use your OS to toggle it, if it has its own full screen keys. Example `MOD`+`F` on `manjaro-i3`.
- Player controls:
    - **A / D:** Move left/right.
    - **W:** Jump.
    - **Space:** Toggle sprite rotating with physics engine.
    - **Enter:** Toggle camera follow ing player.

- All the content for the game is located inside the `content/game/content` folder. All the content inside the last `content` folder there is copied automatically to the output bin path via `CMake` when the `CMakeLists.txt` project is loaded. If any changes are done to these files, you can make sure the last files are updated by simply reloading the `CMakeLists.txt` file related to `raylib_template`. In `CLion` this is as easy as right-clicking the `CMakeLists.txt` file and choosing `Reload CMake Project`.

- Maps: The maps are created using `Tiled`, and uses a `tiled-project` on the top level. If you want to modify the map files, make sure things are loaded through opening the `gamedev.tiled-project` in `Tiled`. The reason why this is important is that some types can only be resolved through the common `tiled-project`.

# Game design document
There is a work-in-progress GDD (game design document) inside the [design](design/README.md) folder.
The idea is to make a GDD using `Markdown` that is easy to access through `GitHub`. It has a few examples written down, based on information that can be found in the `content/docs` folder.