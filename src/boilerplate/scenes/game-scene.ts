import { Bird } from "../objects/bird";
import { Pipe } from "../objects/pipe";

export class GameScene extends Phaser.Scene {
  private bird: Bird;
  private pipes: Phaser.GameObjects.Group;
  private background: Phaser.GameObjects.TileSprite;
  private scoreText: Phaser.GameObjects.BitmapText;
  private timer: Phaser.Time.TimerEvent;

  constructor() {
    super({
      key: "GameScene"
    });
  }

  init(): void {
    //
  }

  create(): void {
    //
  }

  update(): void {
    //
  }
}
