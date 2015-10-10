<?hh //partial

namespace package\spec;

use package\ClassObject;
use package\SourceFile;
use package\ClassTypeMatcher;

describe(ClassTypeMatcher::class, function () {
  beforeEach(function () {
    $this->classFile = new ClassObject(
      new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh')),
      'package\\spec\\fixtures',
      realpath(__DIR__ . '/fixtures')
    );
  });
  describe('classType()', function () {
    beforeEach(function () {
      $this->matcher = ClassTypeMatcher::classType();
    });
    context('when matched', function () {
      it('returns true', function () {
        expect($this->matcher->matches($this->classFile))->toBeTrue();
      });
    });
  });
  describe('abstractClassType()', function () {
    beforeEach(function () {
      $this->matcher = ClassTypeMatcher::abstractClassType();
    });
    context('when unmatched', function () {
      it('returns false', function () {
        expect($this->matcher->matches($this->classFile))->toBeFalse();
      });
    });
  });
  describe('traitType()', function () {
    beforeEach(function () {
      $this->matcher = ClassTypeMatcher::traitType();
    });
    context('when unmatched', function () {
      it('returns false', function () {
        expect($this->matcher->matches($this->classFile))->toBeFalse();
      });
    });
  });
  describe('interfaceType()', function () {
    beforeEach(function () {
      $this->matcher = ClassTypeMatcher::interfaceType();
    });
    context('when unmatched', function () {
      it('returns false', function () {
        expect($this->matcher->matches($this->classFile))->toBeFalse();
      });
    });
  });
});
