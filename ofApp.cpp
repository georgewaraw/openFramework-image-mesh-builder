#include "ofApp.h"

void ofApp::setup( ) {

    ofSetBackgroundAuto( false );
    ofBackground( 0 );
    ofSetFrameRate( frameRate );

    image.load( imageName );
    image.resize( screenWidth*imageScale, screenHeight*imageScale );

    mesh.setMode( OF_PRIMITIVE_LINES );
    mesh.enableIndices( );
    mesh.enableColors( );

    for ( int x=0; x<image.getWidth(); ++x ) {
        for ( int y=0; y<image.getHeight(); ++y ) {

            auto c = image.getColor( x, y );
            float l = c.getLightness( );
            if ( l > pixelIntensityThreshold ) {

                float z = ofMap( l, 0.0, 255.0, -meshDepthLimit, meshDepthLimit );
                ofVec3f p( x/imageScale, y/imageScale, z );

                mesh.addVertex( p );
                mesh.addColor( c );

                ofVec3f t = ofVec3f(
                    ofRandom(0.0,100'000.0), ofRandom(0.0,100'000.0), ofRandom(0.0,100'000.0) );
                timeOffsets.push_back( t );
            }

        }
    }

    vertexCount = mesh.getNumVertices( );

    for ( int a=0; a<vertexCount; ++a ) {

        ofVec3f va = mesh.getVertex( a );
        for ( int b=a+1; b<vertexCount; ++b ) {

            ofVec3f vb = mesh.getVertex( b );
            float d = va.distance( vb );
            if ( d < vertexDistanceThreshold ) {

                mesh.addIndex( a );
                mesh.addIndex( b );
            }

        }

    }

}

void ofApp::draw( ) {

    ofSetColor( 0, 0, 0, motionBlurStrength );
    ofDrawRectangle( 0, 0, screenWidth, screenHeight );
    ofSetColor( 255 );

    for ( int i=0; i<vertexCount; ++i ) {

        ofVec3f v = mesh.getVertex( i );
        float t = ofGetElapsedTimef( );
        ofVec3f to = timeOffsets[ i ];

        v.x += ofSignedNoise( t * timeScale + to.x ) * vertexDisplacementScale;
        v.y += ofSignedNoise( t * timeScale + to.y ) * vertexDisplacementScale;
        v.z += ofSignedNoise( t * timeScale + to.z ) * vertexDisplacementScale;
        mesh.setVertex( i, v );

    }

    if ( cameraDirection == "towards" ) {

        cameraPosition += cameraSpeed;
        if ( cameraPosition > cameraEndPosition ) cameraDirection = "away";

    } else {

        cameraPosition -= cameraSpeed;
        if ( cameraPosition <= cameraStartPosition ) cameraDirection = "towards";

    }
    camera.begin( );
        ofPushMatrix( );

            ofTranslate( -screenWidth/2, -screenHeight/2, cameraPosition );
            mesh.draw( );

        ofPopMatrix( );
    camera.end( );

}
