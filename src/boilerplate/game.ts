import "phaser";
import { BootScene } from "./scenes/boot-scene";
import { GameScene } from "./scenes/game-scene";
import { MainMenuScene } from "./scenes/main-menu-scene";

const config: Phaser.Types.Core.GameConfig = {
  title: "BattleShip",
  version: "1.0",
  width: 390,
  height: 600,
  type: Phaser.AUTO,
  parent: "game",
  scene: [BootScene/*, MainMenuScene, GameScene*/],
  input: {
    keyboard: true
  },
  physics: {
    default: "arcade",
    arcade: {
      gravity: { y: 300 }
    }
  },
  backgroundColor: "#98d687",
  render: { pixelArt: true, antialias: false }
};

export class Game extends Phaser.Game {
  constructor(config: Phaser.Types.Core.GameConfig) {
    super(config);
  }
}

window.addEventListener("load", () => {
  var game = new Game(config);
});