<?hh //strict

namespace HHPack\Package\Test;

use HHPack\Package\SourceFile;
use HHPack\Package\Test\Fixtures\Example1;
use HackPack\HackUnit\Contract\Assert;

final class SourceFileTest {
  <<Test>>
  public function startsWithWhenMatched(Assert $assert): void {
    $sourceFile = new SourceFile(realpath(__DIR__.'/fixtures/Example1.hh'));
    $assert->bool($sourceFile->startsWith(__DIR__))->is(true);
  }

  <<Test>>
  public function startsWithWhenUnmatched(Assert $assert): void {
    $sourceFile = new SourceFile(realpath(__DIR__.'/fixtures/Example1.hh'));
    $assert->bool($sourceFile->startsWith('/Foo'))->is(false);
  }

  <<Test>>
  public function endsWithWhenMatched(Assert $assert): void {
    $sourceFile = new SourceFile(realpath(__DIR__.'/fixtures/Example1.hh'));
    $assert->bool($sourceFile->endsWith('/Example1.hh'))->is(true);
  }

  <<Test>>
  public function endsWithWhenUnmatched(Assert $assert): void {
    $sourceFile = new SourceFile(realpath(__DIR__.'/fixtures/Example1.hh'));
    $assert->bool($sourceFile->endsWith(__DIR__))->is(false);
  }
}
