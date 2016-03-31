<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\ClassObject;
use hhpack\package\spec\fixtures\Base;
use hhpack\package\spec\fixtures\Example1;
use ReflectionClass;

describe(ClassObject::class, function () {
  beforeEach(function () {
    $this->classFile = new ClassObject(new ReflectionClass((string) Example1::class));
  });
  describe('fullName()', function () {
    it('returns class name', function() {
      expect($this->classFile->fullName())->toBe((string) Example1::class);
    });
  });
  describe('name()', function () {
    it('returns short class name', function() {
      expect($this->classFile->name())->toBe('Example1');
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
        expect($instance)->toBeAnInstanceOf((string) Example1::class);
        expect($instance->getName())->toBe('foo');
      });
    });
    context('when not specify the parameters', function() {
      it('create an instance', function() {
        expect($this->classFile->instantiate())->toBeAnInstanceOf((string) Example1::class);
      });
    });
  });
});
