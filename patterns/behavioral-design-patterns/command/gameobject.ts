export class GameObject extends Phaser.GameObjects.Image {
  constructor(params) {
    super(params.scene, params.x, params.y, params.key);

    this.initImage();

    this.scene.add.existing(this);
  }

  private initImage(): void {
    this.setOrigin(0, 0);
  }

  public shoot(): void {}
  public updatePosition(tile: Phaser.Tilemaps.Tile): void {}
}
