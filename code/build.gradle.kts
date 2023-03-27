import com.github.jengelman.gradle.plugins.shadow.tasks.ShadowJar

plugins {
    kotlin("jvm") version "1.7.10"

    id("com.github.johnrengelman.shadow") version "7.1.2"

    // Apply the application plugin to add support for building an application
    application
}

repositories {
    mavenCentral()
}

dependencies {
    implementation(kotlin("stdlib"))
}

application {
    // Define the main class for the application
    mainClass.set("code.MakePkiPathKt")
}

tasks.withType<ShadowJar> {
    archiveClassifier.set("")
    archiveVersion.set("")
}
