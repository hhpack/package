<?hh //partial

namespace package\spec;

use package\ClassObject;
use package\SourceFile;
use package\spec\fixtures\Base;

describe(ClassObject::class, function () {
  beforeEach(function () {
    $this->classFile = new ClassObject(
      new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh')),
      'package\\spec\\fixtures',
      realpath(__DIR__ . '/fixtures')
    );
  });
  describe('getClassName()', function () {
    it('returns class name', function() {
      expect($this->classFile->getClassName())->toBe('package\\spec\\fixtures\\Example1');
    });
  });
  describe('getShortClassName()', function () {
    it('returns short class name', function() {
      expect($this->classFile->getShortClassName())->toBe('Example1');
    });
  });
  describe('isSubclassOf()', function () {
    context('when subclass', function () {
      it('returns true', function() {
        expect($this->classFile->isSubclassOf(Base::class))->toBeTrue();
      });
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
