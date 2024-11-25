using lab9;

var inputReader = new InputReader();
var didi = new Tamagotchi("Didi", 15, 3000, "dd", inputReader);
var mimi = new Tamagotchi("Mimi", 15, 2000, "mm", inputReader);

var d = didi.Run();
var m = mimi.Run();
inputReader.ReadKeys();