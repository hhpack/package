<?hh //partial

namespace hhpack\package\spec;

use hhpack\package\ClassObject;
use hhpack\package\SourceFile;
use hhpack\package\ClassNameMatcher;

describe(ClassNameMatcher::class, function () {
  beforeEach(function () {
    $this->classFile = new ClassObject(
      new SourceFile(realpath(__DIR__ . '/fixtures/Example1.hh')),
      'hhpack\\package\\spec\\fixtures',
      realpath(__DIR__ . '/fixtures')
    );
  });
  describe('startsWith()', function () {
    beforeEach(function () {
      $this->matcher = ClassNameMatcher::startsWith('Exa');
    });
    context('when matched', function () {
      it('returns true', function () {
        expect($this->matcher->matches($this->classFile))->toBeTrue();
      });
    });
  });
  describe('endsWith()', function () {
    beforeEach(function () {
      $this->matcher = ClassNameMatcher::endsWith('1');
    });
    context('when matched', function () {
      it('returns true', function () {
        expect($this->matcher->matches($this->classFile))->toBeTrue();
      });
    });
  });
});
