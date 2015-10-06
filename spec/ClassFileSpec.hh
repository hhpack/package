<?hh //partial

namespace package\spec;

use package\ClassFile;

describe(ClassFile::class, function () {
  beforeEach(function () {
    $this->classFile = new ClassFile(
      realpath(__DIR__ . '/fixtures/Example1.hh'),
      'package\\spec\\fixtures\\',
      realpath(__DIR__ . '/fixtures')
    );
  });
  describe('getClassName()', function () {
    it('returns class name', function() {
      expect($this->classFile->getClassName())->toBe('package\\spec\\fixtures\\Example1');
    });
  });
});
