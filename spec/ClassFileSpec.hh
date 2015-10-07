<?hh //partial

namespace package\spec;

use package\ClassFile;

describe(ClassFile::class, function () {
  beforeEach(function () {
    $this->classFile = new ClassFile(
      realpath(__DIR__ . '/fixtures/Example1.hh'),
      'package\\spec\\fixtures',
      realpath(__DIR__ . '/fixtures')
    );
  });
  describe('getClassName()', function () {
    it('returns class name', function() {
      expect($this->classFile->getClassName())->toBe('package\\spec\\fixtures\\Example1');
    });
  });
  describe('instantiate()', function () {
    context('when specify the parameters', function() {
      it('create an instance with the parameter', function() {
        $instance = $this->classFile->instantiate([ 'foo' ]);
        expect($instance)->toBeAnInstanceOf('package\\spec\\fixtures\\Example1');
        expect($instance->getName())->toBe('foo');
      });
    });
    context('when not specify the parameters', function() {
      it('create an instance', function() {
        expect($this->classFile->instantiate())->toBeAnInstanceOf('package\\spec\\fixtures\\Example1');
      });
    });
  });
});
