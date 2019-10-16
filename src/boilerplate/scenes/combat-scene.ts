export class CombatScene extends Phaser.Scene {
    private phaserSprite: Phaser.GameObjects.Sprite;

    constructor() {
        super({
            key: "CombatScene"
        });
    }

    preload(): void {
        //
        console.log('init CombatScene');
    }

    create(): void {
        //
    }
}
