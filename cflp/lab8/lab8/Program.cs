using lab8;

var inputReader = new InputReader();
var charListener1 = new CharListener('a', inputReader);
var charListener2 = new CharListener('x', inputReader);
var complexListener = new ComplexListener(5, inputReader);

inputReader.ReadKeys();
