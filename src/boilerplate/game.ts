import "phaser";
// import "phaserDebugDraw"; //phaserDebug
import DebugDrawPlugin from 'phaser-plugin-debug-draw';
import { BootScene } from "./scenes/boot-scene";
import { MainMenuScene } from "./scenes/main-menu-scene";
import { CombatScene } from "./scenes/combat-scene";
// import Debug = Phaser.Plugins.Debug;

const config: Phaser.Types.Core.GameConfig = {
  title: "Battle Ship",
  version: "0.0.1",
  url: "someurl.com",
  width: 390,
  height: 600,
  type: Phaser.AUTO,
  parent: "game",
  scene: [BootScene, MainMenuScene, CombatScene],
  // plugins: {
  //   global: [
  //     { key: 'DebugDrawPlugin', plugin: DebugDrawPlugin, mapping: 'debugDraw' }
  //   ]
  // },
  input: {
    keyboard: true,
    mouse: true,
    touch: true
  },
  physics: {
    default: "arcade",
    arcade: {
      debug: true,
      gravity: { y: 300 }
    }
  },
  backgroundColor: "#091622",
  render: { pixelArt: true, antialias: false }
};

export class Game extends Phaser.Game {
  constructor(config: Phaser.Types.Core.GameConfig) {
    super(config);
  }
}

window.addEventListener("load", () => {
  var game = new Game(config);
  game.instance = {};
});