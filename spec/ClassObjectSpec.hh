<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\ClassObject;
use hhpack\package\SourceFile;
use hhpack\package\spec\fixtures\Base;

describe(ClassObject::class, function () {
  beforeEach(function () {
    $this->classFile = new ClassObject(
      new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh')),
      'hhpack\\package\\spec\\fixtures',
      realpath(__DIR__ . '/fixtures')
    );
  });
  describe('getFullName()', function () {
    it('returns class name', function() {
      expect($this->classFile->getFullName())->toBe('hhpack\\package\\spec\\fixtures\\Example1');
    });
  });
  describe('getName()', function () {
    it('returns short class name', function() {
      expect($this->classFile->getName())->toBe('Example1');
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
        expect($instance)->toBeAnInstanceOf('hhpack\\package\\spec\\fixtures\\Example1');
        expect($instance->getName())->toBe('foo');
      });
    });
    context('when not specify the parameters', function() {
      it('create an instance', function() {
        expect($this->classFile->instantiate())->toBeAnInstanceOf('hhpack\\package\\spec\\fixtures\\Example1');
      });
    });
  });
});
