import {ScrollingBackground} from "../objects/scrolling-background";
import {Player} from "../objects/player";

export class CombatScene extends Phaser.Scene {
    private player; //TODO add type

    private backgrounds: ScrollingBackground;

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
        this.player = new Player(
            this,
            this.cameras.main.width * 0.5,
            this.cameras.main.height * 0.80,
            "sprPlayer"
        );
        this.game.instance.backgrounds.setScene(this);
        // todo вынести аудиоменеджер в отдельный класс
        this.game.instance.sfx.mainTheme.stop();
        this.game.instance.sfx.combatTheme.play();
    }

    update(): void {
        this.game.instance.backgrounds.update();
    }
}
